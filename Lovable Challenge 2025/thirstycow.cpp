#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Use 64-bit integers
using ll = long long;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    ll max_water = 0;
    for (int i = 0; i < N; ++i) {
        ll a;
        cin >> a;
        if (a > max_water) {
            max_water = a;
        }
    }

    cout << max_water << endl;

    return 0;
}