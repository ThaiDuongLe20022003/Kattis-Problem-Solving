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
vector<int> adj[MAXN];
int deg[MAXN];
bool used[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    rep(i, 0, n-1) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
        deg[u]++;
        deg[v]++;
    }

    vi out;
    priority_queue<pii> q;
    rep(i, 0, n) {
        q.push(mp(deg[i], i));
    }

    vi toadd;
    bool ok = true;
    while (sz(out) < n) {
        int cand = -1;
        while (cand == -1) {
            if (q.empty()) {
                ok = false;
                break;
            }
            pii top = q.top(); q.pop();
            if (deg[top.second] == top.first) {
                cand = top.second;
            }
        }
        if (!ok) break;

        used[cand] = true;
        out.pb(cand);
        for (int x : toadd) {
            q.push(mp(deg[x], x));
        }
        toadd.clear();
        for (int nxt : adj[cand]) {
            if (used[nxt]) continue;

            deg[nxt]--;
            toadd.pb(nxt);
        }
    }

    if (ok) {
        for (int x : out) cout << x+1 << ' ';
        cout << endl;
    } else {
        cout << -1 << endl;
    }
}