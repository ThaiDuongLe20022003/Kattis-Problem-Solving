#include<bits/stdc++.h>

using namespace std;
#define pii pair<int, int>
typedef long long ll;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1);
const int N = 110;

void solve() {
    int n;
    cin >> n;
    map<string, array<int, 3> > mp;
    int z = 0;
    for (int i = 0; i < n; ++i) {
        string a, b;
        int x;
        cin >> a >> b >> x;

        if (b == "left") {
            mp[a][0] += x;
        } else if (b == "right") {
            mp[a][1] += x;
        } else {
            mp[a][2] += x;
        }
    }

    int res = 0, mark = 0;
    for (auto X: mp) {
        string a = X.first;
        z += mp[a][0] + mp[a][1] + mp[a][2];

        if (mp[a][0] == 0 && mp[a][1] == 0 && mp[a][2] > 0) res += 1;
        else res += max(mp[a][0], mp[a][1]);
    }

    if (res != z) {
        cout << res + 1 << '\n';
    } else cout << "impossible\n";

}

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int _ = 1;
    while (_--) {
        solve();
    }
    return 0;
}