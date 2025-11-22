#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_R 100
#define MAX_C 100

typedef struct {
    int parent[MAX_R * MAX_C + 1];
    int size;
} DSU;

void dsu_init(DSU* dsu, int n) {
    dsu->size = n;
    for (int i = 0; i <= n; i++) {
        dsu->parent[i] = i;
    }
}

int dsu_find(DSU* dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    return dsu->parent[i] = dsu_find(dsu, dsu->parent[i]);
}

void dsu_unite(DSU* dsu, int i, int j) {
    int root_i = dsu_find(dsu, i);
    int root_j = dsu_find(dsu, j);
    if (root_i != root_j) {
        dsu->parent[root_i] = root_j;
    }
}

typedef struct {
    int r, c;
} Point;

char grid[MAX_R][MAX_C];
bool visited_island[MAX_R][MAX_C];
bool visited_bridge[MAX_R][MAX_C];
int island_id_grid[MAX_R][MAX_C];
int R, C;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool is_valid(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

void bfs_island(int r, int c, int id) {
    Point queue[MAX_R * MAX_C];
    int front = 0, rear = 0;
    
    queue[rear++] = (Point){r, c};
    visited_island[r][c] = true;
    island_id_grid[r][c] = id;

    while (front < rear) {
        Point curr = queue[front++];
        
        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            if (is_valid(nr, nc) && !visited_island[nr][nc] && 
                (grid[nr][nc] == '#' || grid[nr][nc] == 'X')) {
                visited_island[nr][nc] = true;
                island_id_grid[nr][nc] = id;
                queue[rear++] = (Point){nr, nc};
            }
        }
    }
}

typedef struct {
    int ids[10];
    int count;
} IslandSet;

IslandSet bfs_find_islands_for_bridge(int r, int c) {
    IslandSet result = {0};
    Point queue[MAX_R * MAX_C];
    int front = 0, rear = 0;
    
    queue[rear++] = (Point){r, c};
    visited_bridge[r][c] = true;
    
    while (front < rear) {
        Point curr = queue[front++];
        
        for (int i = 0; i < 4; i++) {
            int nr = curr.r + dr[i];
            int nc = curr.c + dc[i];
            
            if (is_valid(nr, nc)) {
                if (grid[nr][nc] == 'B' && !visited_bridge[nr][nc]) {
                    visited_bridge[nr][nc] = true;
                    queue[rear++] = (Point){nr, nc};
                } else if (grid[nr][nc] == 'X') {
                    int island_id = island_id_grid[nr][nc];
                    if (island_id != 0) {
                        // Add to set if not already present
                        bool found = false;
                        for (int j = 0; j < result.count; j++) {
                            if (result.ids[j] == island_id) {
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            result.ids[result.count++] = island_id;
                        }
                    }
                }
            }
        }
    }
    return result;
}

int main() {
    char line[MAX_C + 2];
    int map_num = 1;
    bool first_map_output = true;
    
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Skip empty lines
        while (line[0] == '\n' && !feof(stdin)) {
            fgets(line, sizeof(line), stdin);
        }
        if (feof(stdin)) break;
        
        if (!first_map_output) {
            printf("\n");
        }
        first_map_output = false;
        
        // Read grid
        R = 0;
        C = strlen(line) - 1; // Remove newline
        if (line[C] == '\n') line[C] = '\0';
        
        strcpy(grid[R++], line);
        
        while (fgets(line, sizeof(line), stdin) != NULL && line[0] != '\n') {
            line[strcspn(line, "\n")] = '\0';
            strcpy(grid[R++], line);
        }
        
        // Initialize arrays
        memset(visited_island, 0, sizeof(visited_island));
        memset(visited_bridge, 0, sizeof(visited_bridge));
        memset(island_id_grid, 0, sizeof(island_id_grid));
        
        // 1. Identify Islands
        int island_count = 0;
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (!visited_island[r][c] && (grid[r][c] == '#' || grid[r][c] == 'X')) {
                    island_count++;
                    bfs_island(r, c, island_count);
                }
            }
        }
        
        // 2. Count Bridges & Connect Islands
        DSU dsu;
        dsu_init(&dsu, island_count);
        int bridge_count = 0;
        int bus_count = island_count;
        
        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                if (grid[r][c] == 'B' && !visited_bridge[r][c]) {
                    bridge_count++;
                    IslandSet connected_islands = bfs_find_islands_for_bridge(r, c);
                    
                    if (connected_islands.count == 2) {
                        int id1 = connected_islands.ids[0];
                        int id2 = connected_islands.ids[1];
                        
                        if (dsu_find(&dsu, id1) != dsu_find(&dsu, id2)) {
                            dsu_unite(&dsu, id1, id2);
                            bus_count--;
                        }
                    }
                }
            }
        }
        
        printf("Map %d\n", map_num++);
        printf("islands: %d\n", island_count);
        printf("bridges: %d\n", bridge_count);
        printf("buses needed: %d\n", bus_count);
        
        if (feof(stdin)) break;
    }
    
    return 0;
}