#include <bits/stdc++.h>

const int N = 1e4 + 7;
using namespace std;

int wei[N];
std::vector<pair<int,int> > g[N];

long long cost[N][2];
long long source[N][2];

const long long INF = 1e18;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    for(int i = 0; i < n; ++i) {
        cin >> wei[i];
        cost[i][0] = INF;
        cost[i][1] = INF;
        source[i][0] = -1;
        source[i][1] = -1;
        
    }
    long long res = INF;
    
    set<tuple<long long,int,int> > kolejka;
        

    for(int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        
        g[a].push_back({b, c});
        g[b].push_back({a, c});
        
        kolejka.insert({wei[b], b, b});
        cost[b][0] = wei[b];
        source[b][0] = b;
        
        kolejka.insert({wei[a], a, a});
        cost[a][0] = wei[a];
        source[a][0] = a;
    }
    
    while(kolejka.size()) {
        auto best = *kolejka.begin();
        kolejka.erase(kolejka.begin());
        
        long long c = get<0>(best);
        int u = get<1>(best);
        int v = get<2>(best);
        
        for(auto ed : g[v]) {
            int t = ed.first;
            long long nc = ed.second + c;
            if(nc < cost[t][0] and source[t][0] != u) {
                kolejka.erase({cost[t][1], source[t][1], t});
                cost[t][1] = cost[t][0];
                source[t][1] = source[t][0];
                cost[t][0] = nc;
                source[t][0] = u;
                
                kolejka.insert({nc, u, t});
            }
            else if(nc < cost[t][1] and u != source[t][0]) {
                kolejka.erase({cost[t][1], source[t][1], t});
                cost[t][1] = nc;
                source[t][1] = u;
                kolejka.insert({nc, u, t});
            }
        }
        
    }
    
    for(int i = 0; i < n; ++i) {
            if(cost[i][1] != INF) {
                res = min(res, cost[i][0] + cost[i][1]);
            }
    }
    
    
    cout << res << '\n';
}