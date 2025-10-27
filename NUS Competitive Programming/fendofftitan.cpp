#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

// Use long long for costs to avoid overflow
using ll = long long;

// The cost tuple: (titans, shamans, length)
// We use ll for all to be safe.
using Cost = tuple<ll, ll, ll>;

// A struct for the priority queue to compare {Cost, Node}
// We want a min-heap, so we use greater<>.
struct PQEntry {
    Cost cost;
    int node;

    // Overload > operator for the min-priority queue
    bool operator>(const PQEntry& other) const {
        // tuple comparison is lexicographical by default
        return cost > other.cost;
    }
};

const ll INF = 1e18; // A large number for infinity

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M, X, Y;
    cin >> N >> M >> X >> Y;

    // Adjacency list: adj[u] -> vector of {v, length, shamans, titans}
    map<int, vector<tuple<int, int, int, int>>> adj;

    for (int i = 0; i < M; ++i) {
        int u, v, w, c;
        cin >> u >> v >> w >> c;

        int titans = (c == 2) ? 1 : 0;
        int shamans = (c == 1) ? 1 : 0;

        adj[u].push_back({v, w, shamans, titans});
        adj[v].push_back({u, w, shamans, titans});
    }

    // dist map: dist[u] -> Cost
    map<int, Cost> dist;
    for (int i = 1; i <= N; ++i) {
        dist[i] = {INF, INF, INF};
    }

    // Priority queue for Dijkstra
    priority_queue<PQEntry, vector<PQEntry>, greater<PQEntry>> pq;

    // Start at node X
    dist[X] = {0, 0, 0};
    pq.push({{0, 0, 0}, X});

    while (!pq.empty()) {
        PQEntry top = pq.top();
        pq.pop();

        Cost current_cost = top.cost;
        int u = top.node;

        // If this is an outdated path, skip it
        if (current_cost > dist[u]) {
            continue;
        }

        // Check all neighbors
        for (auto& edge : adj[u]) {
            int v = get<0>(edge);
            int length = get<1>(edge);
            int shamans = get<2>(edge);
            int titans = get<3>(edge);

            Cost new_cost = {
                get<0>(current_cost) + titans,
                get<1>(current_cost) + shamans,
                get<2>(current_cost) + length
            };

            // If we found a better path
            if (new_cost < dist[v]) {
                dist[v] = new_cost;
                pq.push({new_cost, v});
            }
        }
    }

    // Get the final result for the destination Y
    Cost final_cost = dist[Y];

    if (get<0>(final_cost) == INF) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        // Output: length, shamans, titans
        cout << get<2>(final_cost) << " " 
             << get<1>(final_cost) << " " 
             << get<0>(final_cost) << endl;
    }

    return 0;
}