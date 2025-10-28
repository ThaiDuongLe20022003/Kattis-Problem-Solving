#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <numeric> // For iota
#include <set>     // For tracking adjacent islands to a bridge

using namespace std;

// --- DSU (Disjoint Set Union) ---
struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0); // Fills with 0, 1, ..., n
    }

    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};
// --- End DSU ---

int R, C;
vector<string> grid;
vector<vector<bool>> visited_island; // Separate visited for island BFS
vector<vector<bool>> visited_bridge; // Separate visited for bridge BFS
vector<vector<int>> island_id_grid;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

bool is_valid(int r, int c) {
    return r >= 0 && r < R && c >= 0 && c < C;
}

// Flood fill (BFS) to identify islands
void bfs_island(int r, int c, int id) {
    queue<pair<int, int>> q;
    q.push({r, c});
    visited_island[r][c] = true;
    island_id_grid[r][c] = id;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nr = curr.first + dr[i];
            int nc = curr.second + dc[i];

            if (is_valid(nr, nc) && !visited_island[nr][nc] && (grid[nr][nc] == '#' || grid[nr][nc] == 'X')) {
                visited_island[nr][nc] = true;
                island_id_grid[nr][nc] = id;
                q.push({nr, nc});
            }
        }
    }
}

// Flood fill (BFS) over a bridge component, finding adjacent islands
set<int> bfs_find_islands_for_bridge(int r, int c) {
    set<int> adjacent_island_ids;
    queue<pair<int, int>> q;

    q.push({r, c});
    visited_bridge[r][c] = true;

    while (!q.empty()) {
        pair<int, int> curr = q.front();
        q.pop();
        int cr = curr.first;
        int cc = curr.second;

        // Check neighbors of the current bridge cell
        for (int i = 0; i < 4; ++i) {
            int nr = cr + dr[i];
            int nc = cc + dc[i];

            if (is_valid(nr, nc)) {
                if (grid[nr][nc] == 'B' && !visited_bridge[nr][nc]) {
                    visited_bridge[nr][nc] = true;
                    q.push({nr, nc});
                } else if (grid[nr][nc] == 'X') {
                    int island_id = island_id_grid[nr][nc];
                    if (island_id != 0) { // Ensure it's part of a found island
                        adjacent_island_ids.insert(island_id);
                    }
                }
            }
        }
    }
    return adjacent_island_ids;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    int map_num = 1;
    bool first_map_output = true;

    while (getline(cin, line)) {
        while (line.empty() && !cin.eof()) {
             getline(cin, line);
        }
        if (cin.eof() && line.empty()) break;

        if (!first_map_output) {
            cout << "\n";
        }
        first_map_output = false;

        grid.clear();
        grid.push_back(line);
        while (getline(cin, line) && !line.empty()) {
            grid.push_back(line);
        }

        R = grid.size();
        C = grid[0].size();

        // --- 1. Identify Islands ---
        visited_island.assign(R, vector<bool>(C, false));
        island_id_grid.assign(R, vector<int>(C, 0));
        int island_count = 0;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (!visited_island[r][c] && (grid[r][c] == '#' || grid[r][c] == 'X')) {
                    island_count++;
                    bfs_island(r, c, island_count);
                }
            }
        }

        // --- 2. Count Bridges & Connect Islands (DSU) ---
        visited_bridge.assign(R, vector<bool>(C, false));
        int bridge_count = 0;
        DSU dsu(island_count);
        int bus_count = island_count;

        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (grid[r][c] == 'B' && !visited_bridge[r][c]) {
                    bridge_count++;
                    set<int> connected_islands = bfs_find_islands_for_bridge(r, c);

                    // Problem guarantees exactly 2 islands are connected per bridge component
                    if (connected_islands.size() == 2) {
                        auto it = connected_islands.begin();
                        int id1 = *it;
                        it++;
                        int id2 = *it;

                        if (dsu.find(id1) != dsu.find(id2)) {
                            dsu.unite(id1, id2);
                            bus_count--;
                        }
                    } else if (connected_islands.size() == 1) {
                         // This case might happen if a bridge connects an island to itself (forms a loop)
                         // Or if an X wasn't properly assigned an island ID (shouldn't happen)
                         // In either case, it doesn't reduce the bus count.
                    }
                     // If size is 0, it's an isolated bridge segment not connected to land, ignore.
                }
            }
        }

        cout << "Map " << map_num++ << "\n";
        cout << "islands: " << island_count << "\n";
        cout << "bridges: " << bridge_count << "\n";
        cout << "buses needed: " << bus_count << "\n";

         if(cin.eof()) break;

    }

    return 0;
}