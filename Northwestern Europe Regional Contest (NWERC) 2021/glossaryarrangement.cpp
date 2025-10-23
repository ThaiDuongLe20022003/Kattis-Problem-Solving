#include<bits/stdc++.h>

using namespace std;

using vi = vector<int>;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, w;
    cin >> n >> w;
    vector<string> s(n);
    for (auto &i: s) cin >> i;
    vector<int> f(n + 1);

    auto dp = [n, w, s, &f](int h) {
        f.assign(n + 1, w + 1);
        f[0] = -1;
        for (int i = 0, mx; i < n; i++) {
            mx = 0;
            for (int j = i; j < n and j < i + h; j++) {
                mx = max(mx, int(s[j].size()));
                f[j + 1] = min(f[j + 1], f[i] + mx + 1);
            }
        }
        return f[n];
    };

    int l = 1, r = n, h = -1;
    for (int mid; l <= r;) {
        mid = (l + r) / 2;
        if (dp(mid) <= w) h = mid, r = mid - 1;
        else l = mid + 1;
    }
    cout << h << " ";
    vi v;
    dp(h);
    for (int i = n, j, mx; i;) {
        j = i, mx = 0;
        do {
            j--;
            mx = max(mx, int(s[j].size()));
        } while (f[i] != f[j] + mx + 1);
        v.push_back(mx), i = j;
    }
    reverse(v.begin(), v.end());
    cout << v.size() << "\n";
    for (auto i: v) cout << i << " ";
    cout << "\n";
    vector<string> res(h);
    for (int i = 0, k = 0; i < v.size(); i++) {
        for (int j = 0; j < h; j++) {
            if (i) res[j] += " ";
            string t;
            if (k < n and s[k].size() <= v[i]) t = s[k++];
            t.resize(v[i], ' ');
            res[j] += t;
        }
    }
    for (auto i: res)
        cout << i << "\n";
    return 0;
}