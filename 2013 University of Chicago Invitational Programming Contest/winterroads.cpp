#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <queue>
#include <functional> // For std::function

using namespace std;

// Using long long for capacity
using ll = long long;

struct Edge {
    int u, v, id;
    ll cap;
    // For sorting
    bool operator>(const Edge& other) const {
        return cap > other.cap;
    }
};

struct DSU {
    vector<int> parent;
    DSU(int n) {
        parent.resize(n + 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

int n, m, e;
vector<Edge> all_edges; // Stores u, v, id, and initial cap
vector<vector<pair<int, int>>> adj; // MSF: {neighbor, road_id}
vector<ll> capacities; // Current capacities, index is road_id

// Query: O(N)
bool check_path(int a, int b, ll w) {
    queue<int> q;
    q.push(a);
    vector<bool> visited(n + 1, false);
    visited[a] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == b) return true;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int r_id = edge.second;
            if (!visited[v] && capacities[r_id] >= w) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return false;
}

// Helper to remove an edge from the MSF adjacency list
void remove_from_adj(int u, int v, int r_id) {
    for (int i = 0; i < adj[u].size(); ++i) {
        if (adj[u][i].first == v && adj[u][i].second == r_id) {
            swap(adj[u][i], adj[u].back());
            adj[u].pop_back();
            break;
        }
    }
    for (int i = 0; i < adj[v].size(); ++i) {
        if (adj[v][i].first == u && adj[v][i].second == r_id) {
            swap(adj[v][i], adj[v].back());
            adj[v].pop_back();
            break;
        }
    }
}

// Find min capacity edge on path u-v in MSF. Returns {min_cap, road_id}
// O(N)
pair<ll, int> find_path_bottleneck(int start, int end) {
    queue<pair<int, pair<ll, int>>> q; // {node, {min_cap_so_far, min_road_id}}
    q.push({start, {2e9, -1}}); // Start with "infinity" capacity
    vector<int> parent(n + 1, 0);
    vector<int> road_to_parent(n + 1, 0);
    vector<bool> visited(n + 1, false);
    visited[start] = true;

    queue<int> bfs_q;
    bfs_q.push(start);
    
    // 1. Find path using BFS
    bool found = false;
    while(!bfs_q.empty()){
        int u = bfs_q.front();
        bfs_q.pop();
        if(u == end) {
            found = true;
            break;
        }
        for(auto& edge : adj[u]){
            int v = edge.first;
            int r_id = edge.second;
            if(!visited[v]){
                visited[v] = true;
                parent[v] = u;
                road_to_parent[v] = r_id;
                bfs_q.push(v);
            }
        }
    }

    if (!found) return {-1, -1}; // No path

    // 2. Walk path back and find min edge
    ll min_cap = 2e9;
    int min_road_id = -1;
    int curr = end;
    while(curr != start) {
        int r_id = road_to_parent[curr];
        if (capacities[r_id] < min_cap) {
            min_cap = capacities[r_id];
            min_road_id = r_id;
        }
        curr = parent[curr];
    }
    return {min_cap, min_road_id};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    all_edges.resize(m + 1);
    capacities.resize(m + 1);
    adj.resize(n + 1);

    vector<Edge> initial_edges;
    for (int i = 1; i <= m; ++i) {
        all_edges[i].id = i;
        cin >> all_edges[i].u >> all_edges[i].v >> all_edges[i].cap;
        capacities[i] = all_edges[i].cap;
        initial_edges.push_back(all_edges[i]);
    }

    // --- Initial MSF Build ---
    sort(initial_edges.begin(), initial_edges.end(), greater<Edge>());
    DSU dsu(n);
    for (const auto& edge : initial_edges) {
        if (dsu.unite(edge.u, edge.v)) {
            adj[edge.u].push_back({edge.v, edge.id});
            adj[edge.v].push_back({edge.u, edge.id});
        }
    }

    cin >> e;
    for (int i = 0; i < e; ++i) {
        char type;
        cin >> type;
        if (type == 'S') {
            int a, b;
            ll w;
            cin >> a >> b >> w;
            cout << check_path(a, b, w) << "\n";
        } else {
            int r_id;
            ll c_new;
            cin >> r_id >> c_new;
            ll c_old = capacities[r_id];
            capacities[r_id] = c_new;
            int u = all_edges[r_id].u;
            int v = all_edges[r_id].v;

            bool was_in_msf = false;
            for(auto& edge : adj[u]) {
                if(edge.first == v && edge.second == r_id) {
                    was_in_msf = true;
                    break;
                }
            }

            if (was_in_msf && c_new < c_old) {
                // --- Breakdown ---
                remove_from_adj(u, v, r_id);

                // Find replacement
                vector<bool> in_T_u(n + 1, false);
                queue<int> q;
                q.push(u);
                in_T_u[u] = true;
                while(!q.empty()){
                    int curr = q.front(); q.pop();
                    for(auto& edge : adj[curr]){
                        if(!in_T_u[edge.first]){
                            in_T_u[edge.first] = true;
                            q.push(edge.first);
                        }
                    }
                }

                ll max_cap = -1;
                int best_r_id = -1;
                for (int j = 1; j <= m; ++j) {
                    if (in_T_u[all_edges[j].u] != in_T_u[all_edges[j].v]) {
                        if (capacities[j] > max_cap) {
                            max_cap = capacities[j];
                            best_r_id = j;
                        }
                    }
                }
                if (best_r_id != -1) {
                    adj[all_edges[best_r_id].u].push_back({all_edges[best_r_id].v, best_r_id});
                    adj[all_edges[best_r_id].v].push_back({all_edges[best_r_id].u, best_r_id});
                }

            } else if (!was_in_msf && c_new > c_old) {
                // --- Repair ---
                pair<ll, int> bottleneck = find_path_bottleneck(u, v);
                ll c_min = bottleneck.first;
                int r_min_id = bottleneck.second;

                if (c_min != -1 && c_new > c_min) {
                    remove_from_adj(all_edges[r_min_id].u, all_edges[r_min_id].v, r_min_id);
                    adj[u].push_back({v, r_id});
                    adj[v].push_back({u, r_id});
                }
            }
        }
    }
    return 0;
}