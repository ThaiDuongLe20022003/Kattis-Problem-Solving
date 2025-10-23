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

ll T;
int a[3];
ll s[3];

int memo[5001][2001];
int dp(int numbags, int num1) {
    if (memo[numbags][num1] != -1) return memo[numbags][num1];

    if (numbags == 0) {
        if (num1 == 0) return 0;
        else return -5;
    }

    int out = -5;
    rep(x1, 0, min(num1+1, 5)) {
        ll rem = T - x1*s[1];
        if (rem < 0) continue;
        
        int rec = dp(numbags-1, num1-x1);
        if (rec == -5) continue;
        int x0 = rem/s[0];
        out = max(out, rec+x0);
    }

    return memo[numbags][num1] = out;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    memset(memo, -1, sizeof memo);

    cin >> T;
    rep(i, 0, 2) cin >> a[i];
    rep(i, 0, 2) cin >> s[i];

    rep(out, 0, 5001) {
        if (dp(out, a[1]) >= a[0]) {
            cout << out << endl;
            return 0;
        }
    }
}