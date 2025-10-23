#include <stdio.h>
#include <string.h>

#define MAX_M 1000

int graph[MAX_M][MAX_M];
int visited[MAX_M];
int m;

void dfs(int node) {
    visited[node] = 1;
    for (int i = 0; i < m; i++) {
        if (graph[node][i] && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    while (n--) {
        scanf("%d", &m);
        
        // Reset graph and visited array
        memset(graph, 0, sizeof(graph));
        memset(visited, 0, sizeof(visited));
        
        int r;
        scanf("%d", &r);
        
        // Build adjacency matrix
        for (int i = 0; i < r; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            graph[u][v] = 1;
            graph[v][u] = 1;
        }
        
        // Count connected components
        int components = 0;
        for (int i = 0; i < m; i++) {
            if (!visited[i]) {
                dfs(i);
                components++;
            }
        }
        
        // Minimum roads to add = components - 1
        printf("%d\n", components - 1);
    }
    
    return 0;
}