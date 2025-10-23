#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define pb push_back
#define mp make_pair

#define MAXN 100'010
int par[MAXN];
int mnedge[MAXN];
int numedges[MAXN];
int numverts[MAXN];

int getPar(int x) {
    if (par[x] == x) return x;
    return par[x] = getPar(par[x]);
}

void Union(int x, int y, int ecost) {
    x = getPar(x);
    y = getPar(y);
    if (x == y) {
        numedges[x]++;
        mnedge[x] = min(ecost, mnedge[x]);
        return;
    }

    mnedge[y] = min(mnedge[y], min(ecost, mnedge[x]));
    numedges[y] += numedges[x]+1;
    numverts[y] += numverts[x];
    par[x] = y;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    rep(i, 0, n) {
        par[i] = i;
        mnedge[i] = 1e8;
        numedges[i] = 0;
        numverts[i] = 1;
    }
    ll out = 0;
    rep(i, 0, m) {
        int u, v, c;
        cin >> u >> v >> c;
        out += c;
        Union(u, v, c);
    }
    int nc = 0;
    rep(i, 0, n) {
        if (getPar(i) == i) nc++;
    }
    if (nc == 1) {
        cout << out << endl;
        return 0;
    }

    rep(i, 0, n) {
        if (getPar(i) == i) {
            if (numedges[i] == numverts[i]) {
                // it's a cycle
                out -= mnedge[i];
            }
        }
    }

    cout << out << endl;
}