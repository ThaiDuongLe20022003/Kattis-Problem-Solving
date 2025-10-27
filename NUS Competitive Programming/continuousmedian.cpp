#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;

// Use long long for sums and elements to prevent overflow
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        ll total_median_sum = 0;
        // Max-heap for lower half
        priority_queue<ll> lower_half;
        // Min-heap for upper half
        priority_queue<ll, vector<ll>, greater<ll>> upper_half;

        for (int i = 0; i < N; ++i) {
            ll num;
            cin >> num;

            // 1. Insert num
            if (lower_half.empty() || num <= lower_half.top()) {
                lower_half.push(num);
            } else {
                upper_half.push(num);
            }

            // 2. Balance Heaps
            if (lower_half.size() > upper_half.size() + 1) {
                upper_half.push(lower_half.top());
                lower_half.pop();
            } else if (upper_half.size() > lower_half.size()) {
                lower_half.push(upper_half.top());
                upper_half.pop();
            }

            // 3. Calculate Current Median
            ll current_median;
            if ((i + 1) % 2 != 0) { // Odd number of elements
                current_median = lower_half.top();
            } else { // Even number of elements
                current_median = (lower_half.top() + upper_half.top()) / 2;
            }

            // 4. Add to Sum
            total_median_sum += current_median;
        }

        cout << total_median_sum << "\n";
    }

    return 0;
}