#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;

string S;
ll memo[20][10][2][2];

ll dp(int pos, int prev_d, bool is_less, bool is_started, bool is_falling) {
    if (pos == S.size()) {
        return is_started; 
    }
    if (memo[pos][prev_d][is_less][is_falling] != -1) {
        return memo[pos][prev_d][is_less][is_falling];
    }

    ll ans = 0;
    int upper_bound = is_less ? 9 : (S[pos] - '0');

    for (int d = 0; d <= upper_bound; ++d) {
        if (!is_started) {
            if (d == 0) {
                ans += dp(pos + 1, 0, true, false, false);
            } else {
                ans += dp(pos + 1, d, is_less || (d < upper_bound), true, false);
            }
        } else {
            if (is_falling) {
                if (d <= prev_d) {
                    ans += dp(pos + 1, d, is_less || (d < upper_bound), true, true);
                }
            } else {
                if (d < prev_d) { 
                    ans += dp(pos + 1, d, is_less || (d < upper_bound), true, true);
                } else { 
                    ans += dp(pos + 1, d, is_less || (d < upper_bound), true, false);
                }
            }
        }
    }

    return memo[pos][prev_d][is_less][is_falling] = ans;
}

bool is_hill_number(const string& s) {
    int n = s.length();
    if (n == 0) return false;
    if (s.find_first_not_of('0') == string::npos) return false; 

    bool falling = false;
    for (size_t i = 0; i < n - 1; ++i) {
        if (s[i] < s[i+1]) {
            if (falling) return false; 
        } else if (s[i] > s[i+1]) {
            falling = true;
        }
    }
    return true;
}

ll solve(string n_str) {
    S = n_str;
    memset(memo, -1, sizeof(memo));
    return dp(0, 0, false, false, false);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string n_str;
    while (cin >> n_str) {
        if (!is_hill_number(n_str)) {
            cout << -1 << endl;
        } else {
            cout << solve(n_str) << endl;
        }
    }

    return 0;
}