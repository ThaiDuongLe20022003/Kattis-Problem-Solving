#include <bits/stdc++.h>

using namespace std;

#define int __int128
using ll = long long;
using pii = pair<int, int>;

int read() {
    int x = 0, f = 1, ch = getchar();
    while ((ch < '0' || ch > '9') && ch != '-') ch = getchar();
    if (ch == '-') f = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') x = (x << 3) + (x << 1) + ch - '0', ch = getchar();
    return x * f;
}

constexpr int inf = 1e15;

int32_t main() {
    int n = read();
    vector<int> a(n + n + 1);
    for (int i = 1; i <= n; i++)
        a[i + n] = a[i] = read();
    n = n * 2;
    auto check = [a, n](int x) -> bool {
        int tot = x;
        stack<pii> stk;
        for (int i = 1; i <= n; i++) {
            if (a[i] <= tot) {
                tot += a[i];
                while (!stk.empty() and stk.top().first <= tot) {
                    tot += stk.top().second;
                    stk.pop();
                }
            } else {
                stk.emplace(a[i], tot - x + a[i]);
                tot = x;
            }
        }
        return stk.empty();
    };

    int l = 0, r = inf, res = -1;
    for (int mid; l <= r;) {
        mid = (l + r) / 2;
        if (check(mid)) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << (ll) res << "\n";
    return 0;
}