#include <bits/stdc++.h>
using namespace std;

struct Passenger {
    int a, b, s;
    int left, right; // seat range they can sit in
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, r, c;
    cin >> n >> r >> c;
    vector<Passenger> passengers(n);
    
    for (int i = 0; i < n; i++) {
        cin >> passengers[i].a >> passengers[i].b >> passengers[i].s;
        passengers[i].left = max(1, passengers[i].a - passengers[i].s);
        passengers[i].right = min(r, passengers[i].a + passengers[i].s);
    }
    
    // Sort by right boundary
    sort(passengers.begin(), passengers.end(), [](const Passenger& a, const Passenger& b) {
        return a.right < b.right;
    });
    
    map<int, int> available; // row -> remaining seats
    for (int i = 1; i <= r; i++) {
        available[i] = c;
    }
    
    int ans = 0;
    for (auto& p : passengers) {
        auto it = available.lower_bound(p.left);
        if (it != available.end() && it->first <= p.right) {
            ans++;
            it->second--;
            if (it->second == 0) {
                available.erase(it);
            }
        }
    }
    
    cout << ans << "\n";
    return 0;
}