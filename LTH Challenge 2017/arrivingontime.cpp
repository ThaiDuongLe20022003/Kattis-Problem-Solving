#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
using ll = long long;

const ll INF = -1; // Use -1 to represent unreached

struct State {
    ll time;
    int node;
    bool operator>(const State& other) const {
        return time < other.time; // Max-priority queue
    }
};

struct Tram {
    int u, v, t0, p, d;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll s;
    cin >> n >> m >> s;

    vector<vector<Tram>> incoming_trams(n);
    for (int i = 0; i < m; ++i) {
        int u, v, t0, p, d;
        cin >> u >> v >> t0 >> p >> d;
        incoming_trams[v].push_back({u, v, t0, p, d});
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    vector<ll> latest_departure(n, INF);

    // Start at the destination at time s
    latest_departure[n - 1] = s;
    pq.push({s, n - 1});

    while (!pq.empty()) {
        auto [time_at_v, v] = pq.top();
        pq.pop();

        if (time_at_v < latest_departure[v]) {
            continue; // Stale entry
        }

        // Look at all trams that *arrive* at v
        for (const auto& tram : incoming_trams[v]) {
            int u = tram.u;
            ll t0 = tram.t0, p = tram.p, d = tram.d;
            
            // We must arrive at v at or before time_at_v
            // Arrival time = t0 + k*p + d
            // t0 + k*p + d <= time_at_v
            
            if (time_at_v < t0 + d) {
                continue; // This tram's first arrival is too late
            }
            
            // k*p <= time_at_v - d - t0
            ll k = (time_at_v - d - t0) / p;
            ll departure_time = t0 + k * p;
            
            if (departure_time > latest_departure[u]) {
                latest_departure[u] = departure_time;
                pq.push({departure_time, u});
            }
        }
    }

    if (latest_departure[0] == INF) {
        cout << "impossible\n";
    } else {
        cout << latest_departure[0] << "\n";
    }

    return 0;
}