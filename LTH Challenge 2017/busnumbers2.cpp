#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    cin >> m;

    // counts[i] = number of ways to write i as a sum of two cubes
    vector<int> counts(m + 1, 0);
    
    // Find the limit for a and b
    int limit = 0;
    while ((long long)(limit + 1) * (limit + 1) * (limit + 1) <= m) {
        limit++;
    }

    for (int a = 1; a <= limit; ++a) {
        long long a3 = (long long)a * a * a;
        // Start b from a to avoid double counting and a=b
        for (int b = a; b <= limit; ++b) {
            long long sum = a3 + (long long)b * b * b;
            if (sum <= m) {
                counts[sum]++;
            } else {
                break; // No need to check larger b
            }
        }
    }

    // Find the largest number <= m with at least 2 representations
    for (int i = m; i >= 1; --i) {
        if (counts[i] >= 2) {
            cout << i << "\n";
            return 0;
        }
    }

    cout << "none\n";
    return 0;
}