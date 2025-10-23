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

constexpr ll INF = 1000000666ll*1000000666ll;

void solve(){
    ll yp, lp, ys, ls;
    std::cin >> yp >> lp >> ys >> ls;

    ll nogi = yp * ys;

    ll winda;
    if(yp < lp){
        winda = lp * ls;
    }else{
        winda = (2*yp-lp) * ls;
    }

    ll podejde = std::abs(yp-lp) * ys + lp * ls;

    std::cout << std::min(podejde, std::min(nogi, winda)) << "\n";
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    std::cin >> t;
    while(t--) solve();

    return 0;
}