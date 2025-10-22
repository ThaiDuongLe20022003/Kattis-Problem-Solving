#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Use 64-bit integers for b and y
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    ll a;
    cin >> N >> a;

    // A set to store all unique (x, y) pairs
    set<pair<int, ll>> pairs;

    for (int i = 0; i < N; ++i) {
        ll b;
        cin >> b;

        ll current_b = b;
        // Iterate x = 1, 2, 3, ...
        for (int x = 1; ; ++x) {
            // Check if a^x divides b_i by checking if a divides (b_i / a^(x-1))
            if (current_b % a == 0) {
                // It does. Update current_b to be b_i / a^x
                current_b /= a;
                
                // The pair is (x, y) where y = b_i / a^x = current_b
                pairs.insert({x, current_b});
            } else {
                // a^x does not divide b_i. Stop checking for this b.
                break;
            }
        }
    }

    // The answer is the total number of unique pairs found.
    cout << pairs.size() << endl;

    return 0;
}