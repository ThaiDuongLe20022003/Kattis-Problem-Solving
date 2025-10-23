#include<bits/stdc++.h>

using namespace std;


int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, a = INT_MIN, b = INT_MIN, c = INT_MAX, d = INT_MAX;
    cin >> n;
    if (n == 1) cout << "4\n", exit(0);
    for (int x, y; n; n--) {
        cin >> x >> y;
        a = max(a, x + y);
        b = max(b, x - y);
        c = min(c, x + y);
        d = min(d, x - y);
    }
    cout << 4 + a + b - c - d + (a == c) + (b == d) << "\n";
    return 0;
}