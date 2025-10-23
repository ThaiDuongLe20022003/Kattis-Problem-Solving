#include <cstdio>
#include <iostream>
#define MOD 1000000007
typedef long long LL;
using namespace std;

LL qpow(LL a, LL b) {
    LL res = 1;
    while (b > 0) {
        if (b % 2) {
            res *= a;
            res %= MOD;
        }
        a *= a;
        a %= MOD;
        b >>= 1;
    }
    return res;
}

LL calc(LL n) {
    if (n < 1) return 0;
    if (n == 1) return 7;
    LL len = n / 2;
    LL res = (((qpow(5, len + 1) + (MOD - 5)) % MOD) * ((MOD + 1) / 4) % MOD +
              (qpow(2, len + 1) + (MOD - 2)) % MOD) % MOD * 2 % MOD;
    if (n & 1) {
        res += qpow(2, len + 1) % MOD + qpow(5, len + 1) % MOD;
        res %= MOD;
    }
    return res;
}

int main() {
    LL n,m;

    cin >> m >> n;
    LL ans = (calc(n) - calc(m - 1) + MOD) % MOD;
    cout << ans << endl;
}