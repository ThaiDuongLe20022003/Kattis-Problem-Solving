#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip> // For setprecision

using namespace std;
using ll = long long;

const ll INF = 1e18;

// --- Min Cost Max Flow (Bellman-Ford / SPFA) ---
struct Edge {
    int to;
    ll capacity, flow, cost;
    int rev;
};

vector<vector<Edge>> adj;
vector<ll> dist;
vector<int> parent_edge;
vector<int> parent_node;
int V;

void add_edge(int u, int v, ll cap, ll cost) {
    Edge fwd = {v, cap, 0, cost, (int)adj[v].size()};
    Edge bwd = {u, 0, 0, -cost, (int)adj[u].size()};
    adj[u].push_back(fwd);
    adj[v].push_back(bwd);
}

// Use SPFA (Shortest Path Faster Algorithm) for negative costs
bool spfa(int s, int t) {
    dist.assign(V, INF);
    parent_edge.assign(V, -1);
    parent_node.assign(V, -1);
    vector<bool> in_queue(V, false);
    queue<int> q;

    dist[s] = 0;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int i = 0; i < adj[u].size(); ++i) {
            Edge& e = adj[u][i];
            if (e.capacity - e.flow > 0 && dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost;
                parent_node[e.to] = u;
                parent_edge[e.to] = i;
                if (!in_queue[e.to]) {
                    q.push(e.to);
                    in_queue[e.to] = true;
                }
            }
        }
    }
    return dist[t] != INF;
}

ll min_cost_max_flow(int s, int t) {
    ll min_cost = 0;
    while (spfa(s, t)) {
        ll path_flow = INF;
        for (int v = t; v != s; v = parent_node[v]) {
            path_flow = min(path_flow, adj[parent_node[v]][parent_edge[v]].capacity - adj[parent_node[v]][parent_edge[v]].flow);
        }
        for (int v = t; v != s; v = parent_node[v]) {
            int u = parent_node[v];
            int edge_idx = parent_edge[v];
            adj[u][edge_idx].flow += path_flow;
            int rev_idx = adj[u][edge_idx].rev;
            adj[v][rev_idx].flow -= path_flow;
            min_cost += path_flow * adj[u][edge_idx].cost;
        }
    }
    return min_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    cin >> n;
    vector<pair<int, ll>> categories(n);
    for (int i = 0; i < n; ++i) cin >> categories[i].first >> categories[i].second;
    
    cin >> s;
    V = n + s + 2; // S, T, N categories, S stores
    adj.resize(V);
    int S = 0, T = V - 1;
    
    // S -> Categories
    for (int i = 0; i < n; ++i) {
        add_edge(S, i + 1, categories[i].second, -categories[i].first);
    }
    
    // Categories -> Stores
    for (int j = 0; j < s; ++j) {
        ll store_cap; int num_cats;
        cin >> store_cap >> num_cats;
        for (int k = 0; k < num_cats; ++k) {
            int cat_id; cin >> cat_id;
            add_edge(cat_id, n + j + 1, INF, 0); // cat_id is 1-based
        }
        // Stores -> T
        add_edge(n + j + 1, T, store_cap, 0);
    }
    
    ll max_profit = -min_cost_max_flow(S, T);
    cout << fixed << setprecision(10) << (double)max_profit / 100.0 << "\n";
    
    return 0;
}