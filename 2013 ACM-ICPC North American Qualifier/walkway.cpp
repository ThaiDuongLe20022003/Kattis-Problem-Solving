#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <iomanip> // For setprecision
#include <limits>  // For numeric_limits

using namespace std;

const double INF = numeric_limits<double>::infinity();

// Structure to represent an edge in the graph
struct Edge {
    int to;
    double cost;
};

// Custom comparator for the priority queue (min-heap)
struct CompareDist {
    bool operator()(const pair<double, int>& a, const pair<double, int>& b) {
        return a.first > b.first;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n && n != 0) {
        vector<tuple<int, int, int>> stones(n);
        set<int> unique_widths_set;

        for (int i = 0; i < n; ++i) {
            int a, b, h;
            cin >> a >> b >> h;
            stones[i] = make_tuple(a, b, h);
            unique_widths_set.insert(a);
            unique_widths_set.insert(b);
        }

        int start_width, end_width;
        cin >> start_width >> end_width;
        unique_widths_set.insert(start_width);
        unique_widths_set.insert(end_width);

        // --- Map widths to node IDs ---
        map<int, int> width_to_id;
        vector<int> id_to_width; // Optional: for debugging
        int current_id = 0;
        for (int width : unique_widths_set) {
            width_to_id[width] = current_id;
            id_to_width.push_back(width);
            current_id++;
        }
        int num_nodes = current_id;

        // --- Build Graph ---
        vector<vector<Edge>> adj(num_nodes);
        for (const auto& stone : stones) {
            int a, b, h;
            tie(a, b, h) = stone;
            double cost = (double)(a + b) * h;
            int u = width_to_id[a];
            int v = width_to_id[b];
            adj[u].push_back({v, cost});
            adj[v].push_back({u, cost});
        }

        // --- Run Dijkstra ---
        int start_node = width_to_id[start_width];
        int end_node = width_to_id[end_width];
        vector<double> dist(num_nodes, INF);
        priority_queue<pair<double, int>, vector<pair<double, int>>, CompareDist> pq;

        dist[start_node] = 0.0;
        pq.push({0.0, start_node});

        while (!pq.empty()) {
            double d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (d > dist[u]) {
                continue;
            }

            if (u == end_node) {
                 // Optimization: stop early if we reach the target
                 break;
            }


            for (const auto& edge : adj[u]) {
                int v = edge.to;
                double weight = edge.cost;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        // --- Output Result ---
        double min_cost_cents = dist[end_node];
        double min_cost_dollars = min_cost_cents / 100.0;

        cout << fixed << setprecision(2) << min_cost_dollars << endl;
    }

    return 0;
}