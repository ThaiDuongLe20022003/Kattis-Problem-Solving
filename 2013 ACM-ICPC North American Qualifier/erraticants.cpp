#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <queue>
#include <set> // Using set for adjacency list to handle duplicates easily

using namespace std;

// Define pair<int, int> as Point for clarity
using Point = pair<int, int>;

// Custom hash for Point if using unordered_map (optional, map works fine)
/*
struct PointHash {
    size_t operator()(const Point& p) const {
        // Simple hash combining x and y
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
*/

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    cin.ignore(); // Consume the rest of the first line
    string dummy_line;
    getline(cin, dummy_line); // Consume the first blank line

    for (int path_num = 0; path_num < n; ++path_num) {
        int s;
        cin >> s;
        cin.ignore(); // Consume the rest of the line with 's'

        map<Point, set<Point>> adj; // Adjacency list using set to avoid duplicate edges
        Point current_pos = {0, 0};
        Point start_node = {0, 0};

        for (int i = 0; i < s; ++i) {
            char dir_char;
            cin >> dir_char;
            cin.ignore(); // Consume potential newline after char

            Point next_pos = current_pos;
            if (dir_char == 'N') {
                next_pos.second++;
            } else if (dir_char == 'E') {
                next_pos.first++;
            } else if (dir_char == 'S') {
                next_pos.second--;
            } else if (dir_char == 'W') {
                next_pos.first--;
            }

            // Add bidirectional edges
            adj[current_pos].insert(next_pos);
            adj[next_pos].insert(current_pos);

            current_pos = next_pos;
        }
        Point food_location = current_pos;

        // Consume the blank line after path description, if not the last path
        if (path_num < n - 1) {
            getline(cin, dummy_line);
        }

        // --- BFS ---
        map<Point, int> dist;
        queue<Point> q;
        int shortest_path = -1; // Default if unreachable (shouldn't happen)

        dist[start_node] = 0;
        q.push(start_node);

        while (!q.empty()) {
            Point u = q.front();
            q.pop();
            int d = dist[u];

            if (u == food_location) {
                shortest_path = d;
                break; // Found the shortest path
            }

            // Check neighbors only if the current node exists in adj
            if (adj.count(u)) {
                 for (const Point& v : adj[u]) {
                    if (dist.find(v) == dist.end()) { // If not visited
                        dist[v] = d + 1;
                        q.push(v);
                    }
                }
            }
        }
        cout << shortest_path << "\n";
    } // End loop over paths

    return 0;
}