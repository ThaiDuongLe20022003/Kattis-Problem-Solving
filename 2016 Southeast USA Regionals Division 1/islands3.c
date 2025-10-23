#include <stdio.h>
#include <string.h>

char grid[52][52];
int visited[52][52];
int r, c;
int hasL;

void dfs(int i, int j) {
    if (i < 0 || i >= r || j < 0 || j >= c) return;
    if (visited[i][j]) return;
    if (grid[i][j] == 'W') return;
    
    if (grid[i][j] == 'L') hasL = 1;
    
    visited[i][j] = 1;
    dfs(i+1, j);
    dfs(i-1, j);
    dfs(i, j+1);
    dfs(i, j-1);
}

int main() {
    scanf("%d %d", &r, &c);
    for (int i = 0; i < r; i++) {
        scanf("%s", grid[i]);
    }
    
    memset(visited, 0, sizeof(visited));
    int islands = 0;
    
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (!visited[i][j] && grid[i][j] != 'W') {
                hasL = 0;
                dfs(i, j);
                if (hasL) islands++;
            }
        }
    }
    
    printf("%d\n", islands);
    return 0;
}