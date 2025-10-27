#include <iostream>
#include <vector>
#include <set>
#include <algorithm> // For std::swap

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    // A set to store all edges from the first tree for fast lookup
    set<pair<int, int>> edges_T1;
    
    // Read the N-1 edges of the first tree
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        
        // Store in canonical form (u, v) where u <= v
        if (u > v) {
            swap(u, v);
        }
        edges_T1.insert({u, v});
    }

    int common_count = 0;
    
    // Read the N-1 edges of the second tree and check for matches
    for (int i = 0; i < N - 1; ++i) {
        int u, v;
        cin >> u >> v;
        
        // Convert to canonical form
        if (u > v) {
            swap(u, v);
        }

        // Check if this edge was in the first tree
        if (edges_T1.count({u, v})) {
            common_count++;
        }
    }

    // The minimum operations is the number of edges that are *not* common.
    int operations = (N - 1) - common_count;
    cout << operations << endl;

    return 0;
}
