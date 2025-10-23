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

int n, m;
std::vector<VI> g;
VI layer;
std::vector<VI> layers;

constexpr int INF = 1000000666;

void bfs(){
    std::queue<int> que;
    std::fill(layer.begin(), layer.end(), INF);
    layer[0] = 0;
    layers[0].push_back(0);
    que.push(0);
    while(SZ(que)){
        int v = que.front();
        que.pop();
        
        TRAV(ch, g[v]) if(layer[ch] == INF){
            layer[ch] = layer[v] + 1;
            layers[layer[v]+1].push_back(ch);
            que.push(ch);
        }
    }

    FOR(i, n) assert(layer[i] != INF);
}

constexpr int LG = 19;
int par[200005][LG];

int lca(int a, int b){
    if(a == b) return a;
    if(layer[a] < layer[b]) std::swap(a, b);
    for(int i = LG-1; i >= 0; --i){
        if(layer[a] - (1<<i) >= layer[b]) a = par[a][i];
    }
    assert(layer[a] == layer[b]);
    if(a == b) return a;
    for(int i = LG-1; i >= 0; --i){
        if(par[a][i] != par[b][i]) a = par[a][i], b = par[b][i];
    }
    return par[a][0];
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> m;
    g.resize(n);
    layer.resize(n);
    layers.resize(n+5);
    FOR(i, m){
        int a, b;
        std::cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    if(n == 1){
        std::cout << 0 << "\n";
        return 0;
    }

    bfs();

    FOR(i, n) FOR(j, LG) par[i][j] = -1;
    VI path;
    path.push_back(0);

    FOR(i, SZ(layers)-1){
        std::vector<PII> vec;
        TRAV(v, layers[i]){
            TRAV(ch, g[v]) if(layer[ch] == i+1){
                vec.push_back(MP(ch, v));
            }
        }
        std::sort(vec.begin(), vec.end());
        TRAV(pr, vec){
            if(par[pr.X][0] == -1){
                par[pr.X][0] = pr.Y;
                path.push_back(pr.X);
            }
        }
    }

    REP(j, 1, LG){
        FOR(i, n){
            par[i][j] = (par[i][j-1] == -1 ? -1 : par[par[i][j-1]][j-1]);
        }
    }

    ll ans = 0;
    FOR(i, SZ(path)-1){
        ans += layer[path[i]] + layer[path[i+1]] - 2 * layer[lca(path[i], path[i+1])];
    }
    std::cout << ans << "\n";

    return 0;
}