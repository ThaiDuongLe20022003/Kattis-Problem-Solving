#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// A pair to store coordinates (row, col)
using Coords = pair<int, int>;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<string> grid(N);
    Coords start_pos;

    // Read the grid and find the Knight's starting position
    for (int r = 0; r < N; ++r) {
        cin >> grid[r];
        for (int c = 0; c < N; ++c) {
            if (grid[r][c] == 'K') {
                // Store 0-based coordinates
                start_pos = {r, c};
            }
        }
    }

    // dist[r][c] stores the minimum steps from 'K' to (r, c)
    // Initialize all to -1 (unvisited)
    vector<vector<int>> dist(N, vector<int>(N, -1));

    // Queue for BFS
    queue<Coords> q;

    // Initialize start position
    q.push(start_pos);
    dist[start_pos.first][start_pos.second] = 0;

    // The 8 possible knight moves
    int dr[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dc[] = {1, -1, 1, -1, 2, -2, 2, -2};

    while (!q.empty()) {
        Coords current = q.front();
        q.pop();

        int r = current.first;
        int c = current.second;
        int d = dist[r][c];

        // Check all 8 moves
        for (int i = 0; i < 8; ++i) {
            int new_r = r + dr[i];
            int new_c = c + dc[i];

            // Check if the new position is valid:
            // 1. Inside the grid bounds
            // 2. Not a '#'
            // 3. Not already visited
            if (new_r >= 0 && new_r < N && new_c >= 0 && new_c < N &&
                grid[new_r][new_c] != '#' && dist[new_r][new_c] == -1) 
            {
                // Valid move: update distance and add to queue
                dist[new_r][new_c] = d + 1;
                q.push({new_r, new_c});
            }
        }
    }

    // The target is (1, 1) (1-based), which is (0, 0) (0-based)
    cout << dist[0][0] << endl;

    return 0;
}