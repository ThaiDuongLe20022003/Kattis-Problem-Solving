#include <bits/stdc++.h>

using namespace std;


int32_t main() {
    int n;
    cin >> n;
    vector<int> a(n + 2), v(720);
    for (int i = 1, x; i <= n; i++) {
        cin >> x >> a[i];
        a[i] = (a[i] + 180) * 2;
    }
    a[n+1] = a[1];
    for (int i = 2, x, y; i <= n+1; i++) {
        x = a[i - 1], y = a[i];
        if (x > y) swap(x, y);
        if (y - x == 360) cout << "yes\n", exit(0);
        if (y - x < 360) {
            for (int j = x; j <= y; j++) v[j] = 1;
        } else {
            for (int j = 0; j <= x; j++) v[j] = 1;
            for (int j = y; j < 720; j++) v[j] = 1;
        }
    }
    for( int i = 0 ; i < 720 ; i ++ )
        if( v[i] == 0 ) cout << "no " << fixed << setprecision(1) << (0.5*i) - 180.0 << "\n", exit(0);
    cout << "yes\n";

    return 0;
}