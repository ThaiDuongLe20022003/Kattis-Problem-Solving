#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Use long long for sums and values
using ll = long long;

const int MAX_TYPES = 6;

// --- Fenwick Tree (BIT) ---
struct FenwickTree {
    vector<int> bit; // Stores counts, so int is sufficient
    int n;

    FenwickTree(int size) {
        n = size + 1;
        bit.assign(n, 0);
    }

    // Adds 'val' to index 'idx' (1-based)
    void add(int idx, int val) {
        for (; idx < n; idx += idx & (-idx)) {
            bit[idx] += val;
        }
    }

    // Queries prefix sum up to 'idx' (1-based)
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & (-idx)) {
            sum += bit[idx];
        }
        return sum;
    }
};
// --- End Fenwick Tree ---

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    vector<ll> values(MAX_TYPES + 1);
    for (int i = 1; i <= MAX_TYPES; ++i) {
        cin >> values[i];
    }

    string initial_types_str;
    cin >> initial_types_str;

    vector<int> gem_types(N + 1);
    vector<FenwickTree> bit_counts(MAX_TYPES + 1, FenwickTree(N));

    // Initialize gem types and BITs
    for (int i = 0; i < N; ++i) {
        int type = initial_types_str[i] - '0';
        gem_types[i + 1] = type;
        bit_counts[type].add(i + 1, 1);
    }

    // Process Queries
    for (int q = 0; q < Q; ++q) {
        int type;
        cin >> type;

        if (type == 1) {
            int k, pi_new;
            cin >> k >> pi_new;

            int pi_old = gem_types[k];
            if (pi_old != pi_new) {
                // Update BIT counts
                bit_counts[pi_old].add(k, -1);
                bit_counts[pi_new].add(k, 1);
                // Update gem type array
                gem_types[k] = pi_new;
            }
        } else if (type == 2) {
            int pi;
            ll vi_new;
            cin >> pi >> vi_new;
            values[pi] = vi_new;
        } else { // type == 3
            int li, ri;
            cin >> li >> ri;

            ll total_sum = 0;
            for (int t = 1; t <= MAX_TYPES; ++t) {
                int count_t = bit_counts[t].query(ri) - bit_counts[t].query(li - 1);
                total_sum += (ll)count_t * values[t];
            }
            cout << total_sum << "\n";
        }
    }

    return 0;
}