#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef long long ll;

char S[20];
ll memo[20][10][2][2];

ll dp(int pos, int prev_d, bool is_less, bool is_started, bool is_falling) {
    if (S[pos] == '\0') {
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

bool is_hill_number(const char* s) {
    int n = strlen(s);
    if (n == 0) return false;
    
    bool has_non_zero = false;
    for (int i = 0; i < n; i++) {
        if (s[i] != '0') {
            has_non_zero = true;
            break;
        }
    }
    if (!has_non_zero) return false;

    bool falling = false;
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] < s[i+1]) {
            if (falling) return false; 
        } else if (s[i] > s[i+1]) {
            falling = true;
        }
    }
    return true;
}

ll solve(char* n_str) {
    strcpy(S, n_str);
    memset(memo, -1, sizeof(memo));
    return dp(0, 0, false, false, false);
}

int main() {
    char n_str[20];
    
    while (scanf("%19s", n_str) == 1) {
        if (!is_hill_number(n_str)) {
            printf("-1\n");
        } else {
            printf("%lld\n", solve(n_str));
        }
    }

    return 0;
}