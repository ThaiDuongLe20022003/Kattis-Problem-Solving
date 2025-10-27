#include <iostream>
#include <vector>
#include <numeric>   // For std::accumulate
#include <algorithm> // For std::min_element

using namespace std;

// Use long long for sums to prevent overflow
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<ll> A(N);
    ll total_sum = 0;
    ll min_cost = -1;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
        total_sum += A[i];
        
        if (min_cost == -1 || A[i] < min_cost) {
            min_cost = A[i];
        }
    }

    // Cost = (N-1) * A_min + (TotalSum - A_min)
    // Or, simplified: Cost = (N-2) * A_min + TotalSum
    // We use the first form as it's more intuitive.
    ll min_span_tree_cost = (ll)(N - 1) * min_cost + (total_sum - min_cost);

    cout << min_span_tree_cost << endl;

    return 0;
}