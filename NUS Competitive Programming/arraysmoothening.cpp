#include <iostream>
#include <vector>
#include <map>
#include <algorithm> // For std::max

using namespace std;

// Use long long for counts and K
using ll = long long;

map<int, int> frequencies;
ll N, K;

// Checks if it's possible to achieve a maximum frequency 'f'
// by removing at most K elements.
bool check(int f) {
    ll removals_needed = 0;
    for (auto const& [value, count] : frequencies) {
        if (count > f) {
            removals_needed += (ll)count - f;
        }
    }
    return removals_needed <= K;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    // Calculate initial frequencies
    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        frequencies[val]++;
    }

    // Binary search for the minimum possible maximum frequency
    int low = 0;
    int high = N; // Max possible frequency is N
    int ans = N;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            // If we can achieve frequency 'mid', try for a lower one
            ans = mid;
            high = mid - 1;
        } else {
            // If 'mid' is too low, we need to allow higher frequency
            low = mid + 1;
        }
    }

    cout << ans << endl;

    return 0;
}