#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // For std::max, std::min

using namespace std;

// Use long long for potentially large numbers
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    // Handle base cases
    if (n <= 2) {
        cout << n << endl;
        return 0;
    }

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // dp[i][j] = length of FLS ending with a[i] and a[j] (i < j)
    vector<vector<int>> dp(n, vector<int>(n, 2)); // Initialize base length to 2

    int max_length = 2; // Minimum possible length for n > 2

    // Iterate through all possible second-to-last elements a[i]
    for (int i = 1; i < n; ++i) {
        // Map to store the last seen index for elements before a[i]
        map<ll, int> last_occurrence;
        for (int k = 0; k < i; ++k) {
            last_occurrence[a[k]] = k;
        }

        // Iterate through all possible last elements a[j] (where j > i)
        for (int j = i + 1; j < n; ++j) {
            ll target = a[j] - a[i];

            // Check if the required previous element (a[k] = target) exists before index i
            if (last_occurrence.count(target)) {
                int k = last_occurrence[target];
                // dp[k][i] stores the length ending at a[k], a[i]
                dp[i][j] = dp[k][i] + 1;
                max_length = max(max_length, dp[i][j]);
            }
            // If target not found, dp[i][j] remains 2 (the initial value)
        }
    }

    cout << max_length << endl;

    return 0;
}