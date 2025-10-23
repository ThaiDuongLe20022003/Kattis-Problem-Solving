#include <bits/stdc++.h>
#define FOR(i, n) for(int i = 0; i < (n); ++i)
#define REP(i, a, b) for(int i = (a); i < (b); ++i)
#define TRAV(i, a) for(auto &i : (a))
#define SZ(x) ((int)(x).size())
#define X first
#define Y second
#define PR std::pair
#define MP std::make_pair
typedef long long ll;
typedef std::vector<int> VI;
typedef std::pair<int, int> PII;

int n, q;
std::vector<VI> g;
VI ans;

void dfs(int v, VI& vec){
    if(SZ(g[v]) == 0){
        TRAV(x, vec) ans[x] = v;
        return;
    }

    if(SZ(g[v]) == 1){
        dfs(g[v][0], vec);
        return;
    }

    std::vector<VI> split(SZ(g[v]));
    FOR(i, SZ(vec)) split[i%SZ(split)].push_back(vec[i]);
    FOR(i, SZ(split)){
        dfs(g[v][i], split[i]);
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> q;
    g.resize(n);
    FOR(i, n-1){
        int a;
        std::cin >> a;
        g[a].push_back(i+1);
    }

    VI xd;
    FOR(i, q) xd.push_back(i);
    ans.resize(q);
    dfs(0, xd);

    TRAV(i, ans) std::cout << i << "\n";

    return 0;
}