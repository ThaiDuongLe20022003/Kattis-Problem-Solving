#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

// Checks if k circles of radius r can be packed into a circle of radius s
bool can_pack(int k, double r, double s) {
    if (r > s) return false;
    if (k == 1) return true;
    if (k == 2) return r <= s / 2.0;
    if (k == 3) return r <= s / (1.0 + 2.0 / sqrt(3.0));
    if (k == 4) return r <= s / (1.0 + sqrt(2.0));
    if (k == 5) return r <= s / (1.0 + sqrt(2.0 * (1.0 + 1.0 / sqrt(5.0))));
    if (k == 6) return r <= s / 3.0;
    if (k == 7) return r <= s / 3.0;
    return false; // n is at most 7
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double s, r;
    int n, z;
    cin >> s >> r >> n >> z;

    // Area constraint: k * r^2 <= (z/100) * s^2
    double max_k_area = floor((z * s * s) / (100.0 * r * r));

    for (int k = n; k >= 1; --k) {
        // Check n constraint (implicit), area constraint, and packing constraint
        if (k <= max_k_area && can_pack(k, r, s)) {
            cout << k << "\n";
            return 0;
        }
    }
    
    // Should always be able to at least place 1
    if (n >= 1 && 1 <= max_k_area && can_pack(1, r, s)) {
         cout << 1 << "\n";
    } else {
         cout << 0 << "\n";
    }

    return 0;
}