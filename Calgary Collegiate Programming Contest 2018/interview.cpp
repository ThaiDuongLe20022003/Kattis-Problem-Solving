#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// Use 64-bit integers for all calculations
using ll = long long;

struct Company {
    ll req_x, req_y;
};

// Standard Fenwick Tree (Binary Indexed Tree)
struct BIT {
    vector<int> tree;
    int n;
    BIT(int size) {
        n = size + 1;
        tree.assign(n, 0);
    }
    // Adds 'val' to index 'idx' (0-based)
    void add(int idx, int val) {
        idx++; // 1-based indexing for BIT
        while (idx < n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }
    // Queries prefix sum up to 'idx' (0-based)
    int query_sum(int idx) {
        idx++; // 1-based indexing
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= idx & (-idx);
        }
        return sum;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll A, B, T, ta, tb;
    cin >> A >> B >> T >> ta >> tb;

    int C;
    cin >> C;

    vector<Company> companies(C);
    set<ll> x_set, y_set;
    x_set.insert(0);
    y_set.insert(0);

    for (int i = 0; i < C; ++i) {
        ll a, b;
        cin >> a >> b;
        companies[i].req_x = max(0LL, a - A);
        companies[i].req_y = max(0LL, b - B);
        x_set.insert(companies[i].req_x);
        y_set.insert(companies[i].req_y);
    }

    // Sort companies by req_x for the sweep-line
    sort(companies.begin(), companies.end(), [](const Company& a, const Company& b) {
        return a.req_x < b.req_x;
    });

    // Create coordinate compression maps
    vector<ll> all_x(x_set.begin(), x_set.end());
    vector<ll> all_y(y_set.begin(), y_set.end());
    map<ll, int> y_to_index;
    for (int i = 0; i < all_y.size(); ++i) {
        y_to_index[all_y[i]] = i;
    }

    BIT bit(all_y.size());
    int max_offers = 0;
    int company_ptr = 0;

    for (ll x : all_x) {
        // 1. Calculate y_max for this x
        ll time_left = T - x * ta;
        if (time_left < 0) {
            break; // No more x-values can be valid
        }
        ll y_max = time_left / tb;

        // 2. Add all new companies to the BIT
        while (company_ptr < C && companies[company_ptr].req_x <= x) {
            ll req_y = companies[company_ptr].req_y;
            int y_idx = y_to_index[req_y];
            bit.add(y_idx, 1);
            company_ptr++;
        }

        // 3. Query the BIT
        // Find the index of the largest y in all_y <= y_max
        auto it = upper_bound(all_y.begin(), all_y.end(), y_max);
        int k = distance(all_y.begin(), it);

        if (k > 0) {
            int count = bit.query_sum(k - 1);
            max_offers = max(max_offers, count);
        }
    }

    cout << max_offers << endl;

    return 0;
}