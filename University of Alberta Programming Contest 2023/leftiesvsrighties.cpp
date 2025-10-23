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

int a[200][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, n;
    cin >> t >> n;
    rep(i, 0, n) {
        int topic;
        char c;
        cin >> topic >> c;
        topic--;
        if (c == 'L') a[topic][0]++;
        else a[topic][1]++;
    }

    int nleft = 0;
    int nright = 0;
    rep(i, 0, t) {
        if (a[i][0] + a[i][1] == 0) {
            cout << -1 << endl;
            return 0;
        }

        if (a[i][0] == 0) {
            nright++;
            a[i][1]--;
        } else if (a[i][1] == 0) {
            nleft++;
            a[i][0]--;
        }
    }

    rep(i, 0, t) {
        if (a[i][0] != 0 && a[i][1] != 0) {
            if (nleft <  nright) {
                a[i][0]--;
                nleft++;
            } else {
                a[i][1]--;
                nright++;
            }
        }
    }

    rep(i, 0, t) {
        while (nleft < nright && a[i][0] != 0) {
            nleft++;
            a[i][0]--;
        }
        while (nleft > nright && a[i][1] != 0) {
            nright++;
            a[i][1]--;
        }
    }

    if (nleft == nright) cout << nleft*2 << endl;
    else cout << -1 << endl;
}