#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> times(n);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
    }
    
    // dp[mask][cloak] = minimum time to reach this state
    // mask: which people are at the dorm (1 = at dorm, 0 = at gate)
    // cloak: 0 = cloak at gate, 1 = cloak at dorm
    vector<vector<int>> dp(1 << n, vector<int>(2, INF));
    
    // Initial state: everyone at gate, cloak at gate
    dp[0][0] = 0;
    
    // Priority queue: {time, mask, cloak}
    priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
    pq.push({0, 0, 0});
    
    while (!pq.empty()) {
        auto [time, mask, cloak] = pq.top();
        pq.pop();
        
        // Skip if we've found a better path to this state
        if (time > dp[mask][cloak]) {
            continue;
        }
        
        // Goal: everyone at dorm
        if (mask == (1 << n) - 1) {
            cout << time << endl;
            return 0;
        }
        
        if (cloak == 0) {
            // Cloak at gate: send people from gate to dorm
            
            // Send 1 person
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) { // Person i at gate
                    int new_mask = mask | (1 << i);
                    int new_time = time + times[i];
                    if (new_time < dp[new_mask][1]) {
                        dp[new_mask][1] = new_time;
                        pq.push({new_time, new_mask, 1});
                    }
                }
            }
            
            // Send 2 people
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    for (int j = i + 1; j < n; j++) {
                        if (!(mask & (1 << j))) {
                            int new_mask = mask | (1 << i) | (1 << j);
                            int new_time = time + max(times[i], times[j]);
                            if (new_time < dp[new_mask][1]) {
                                dp[new_mask][1] = new_time;
                                pq.push({new_time, new_mask, 1});
                            }
                        }
                    }
                }
            }
        } else {
            // Cloak at dorm: send people from dorm to gate
            
            // Send 1 person back
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) { // Person i at dorm
                    int new_mask = mask ^ (1 << i);
                    int new_time = time + times[i];
                    if (new_time < dp[new_mask][0]) {
                        dp[new_mask][0] = new_time;
                        pq.push({new_time, new_mask, 0});
                    }
                }
            }
            
            // Send 2 people back
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    for (int j = i + 1; j < n; j++) {
                        if (mask & (1 << j)) {
                            int new_mask = mask ^ (1 << i) ^ (1 << j);
                            int new_time = time + max(times[i], times[j]);
                            if (new_time < dp[new_mask][0]) {
                                dp[new_mask][0] = new_time;
                                pq.push({new_time, new_mask, 0});
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Should never reach here
    return 0;
}