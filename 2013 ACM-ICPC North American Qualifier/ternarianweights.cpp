#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath> // Not strictly needed, but useful for powers

using namespace std;

// Use long long for weights
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    bool first_case = true;
    while (n--) {
        if (!first_case) {
            cout << "\n"; // Blank line between test cases
        }
        first_case = false;

        ll x;
        cin >> x;

        vector<ll> left_weights;
        vector<ll> right_weights;
        ll current_power_of_3 = 1;

        while (x > 0) {
            int rem = x % 3;
            if (rem == 1) {
                right_weights.push_back(current_power_of_3);
                x -= 1; // Prepare for division by 3
            } else if (rem == 2) {
                left_weights.push_back(current_power_of_3);
                x += 1; // Prepare for division by 3 (carry)
            }
            // If rem == 0, do nothing

            x /= 3;
            // Prevent overflow if x is very large initially
            if (x > 0) {
                 if (current_power_of_3 > numeric_limits<ll>::max() / 3) {
                     // Handle potential overflow, though unlikely with x <= 10^9
                     break;
                 }
                current_power_of_3 *= 3;
            }
        }

        // Sort in descending order
        sort(left_weights.rbegin(), left_weights.rend());
        sort(right_weights.rbegin(), right_weights.rend());

        // Print results
        cout << "left pan:";
        for (ll weight : left_weights) {
            cout << " " << weight;
        }
        cout << "\n";

        cout << "right pan:";
        for (ll weight : right_weights) {
            cout << " " << weight;
        }
        cout << "\n";
    }

    return 0;
}