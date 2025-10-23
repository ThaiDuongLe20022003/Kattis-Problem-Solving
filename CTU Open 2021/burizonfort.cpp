#include <bits/stdc++.h>
using namespace std;

#define FOR(i, j, k, l) for(int i = (j); i < (k); i += (l))
#define FORD(i, j, k, l) for(int i =(j); i >= (k); i -= (l))
#define REP(i, n) FOR(i, 0, n, 1)
#define REPD(i, n) FORD(i, n, 0, 1)
typedef long long ll;
const ll INFF = (ll)1e18;
const int INF = (int)1e9;

const int lim = 1e6+5;
bool prime[lim];
vector<int> primes;

void sieve()
{
    for(int i = 2; i < lim; i++)
        prime[i] = true;
    for(int i = 2; i <= 1005; i++)
    {
        if(!prime[i])
            continue;
        primes.push_back(i);
        for(int j = 2*i; j < lim; j += i)
            prime[j] = false;
    }
    for(int i = 1006; i < lim; i++)
        if(prime[i])
            primes.push_back(i);
}

vector<ll> divisors(ll m)
{
    vector<ll> divs = {1};
    for(auto p : primes)
    {
        vector<ll> exps = {1};
        while(m % p == 0)
        {
            exps.push_back(exps.back() * p);
            m /= p;
        }
        if(exps.size() == 1)
            continue;
        vector<ll> newdivs;
        for(auto d : divs)
            for(auto e : exps)
                newdivs.push_back(d * e);
        divs = newdivs;
    }
    vector<ll> newdivs = divs;
    if(m > 1)
        for(auto d : divs)
            newdivs.push_back(d * m);
    divs = newdivs;
    sort(divs.begin(), divs.end());
    return divs;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    sieve();
    while(t--)
    {
        ll m;
        cin >> m;
        vector<ll> divs = divisors(m);
        bool ok = true;
        ll pref = 0;
        for(auto d : divs)
        {
            if(pref + 1 < d)
                ok = false;
            pref += d;
        }
        if(ok)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}