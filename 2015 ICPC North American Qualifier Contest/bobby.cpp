#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to compute nCr (n choose r)
// Since n is small (max 10), we can use a precomputed table or a simple iterative function.
// We will use a simple iterative function to avoid global state and keep it clean.
long double combinations(int n, int k) {
    if (k < 0 || k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    if (k > n / 2) {
        k = n - k;
    }
    long double res = 1.0;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

void solve() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N_cases;
    if (!(cin >> N_cases)) return;

    // Set precision for floating point output, although we only need a comparison.
    // cout << fixed << setprecision(10);

    while (N_cases--) {
        // R: required value (>= R)
        // S: number of sides on the die (1 to S)
        // X: required number of successful rolls (at least X)
        // Y: total number of rolls
        // W: payout multiplier
        int R, S, X, Y, W;
        if (!(cin >> R >> S >> X >> Y >> W)) return;

        // 1. Calculate the probability of a single successful roll (p_success).
        // A successful roll is a value >= R.
        // The possible successful outcomes are R, R+1, ..., S.
        // Number of successful outcomes = S - R + 1.
        // Total possible outcomes = S.
        // p_success = (S - R + 1) / S.
        long double p_success = (long double)(S - R + 1) / S;
        
        // If R > S, it's impossible to succeed, p_success = 0.
        if (R > S) {
            p_success = 0.0;
        }

        // 2. Calculate the probability of failure (p_failure).
        // p_failure = 1 - p_success.
        long double p_failure = 1.0 - p_success;

        // 3. Calculate the probability of winning the bet (P_win).
        // Bobby wins if he gets at least X successful rolls out of Y total rolls.
        // This is a binomial probability problem: P(k >= X) = sum_{k=X}^{Y} P(k successful rolls).
        // P(k) = C(Y, k) * (p_success)^k * (p_failure)^(Y-k).
        
        long double P_win = 0.0;
        
        // Iterate from k = X to Y
        for (int k = X; k <= Y; ++k) {
            // C(Y, k)
            long double nCk = combinations(Y, k);
            
            // (p_success)^k
            long double p_succ_k = pow(p_success, k);
            
            // (p_failure)^(Y-k)
            long double p_fail_Y_k = pow(p_failure, Y - k);
            
            P_win += nCk * p_succ_k * p_fail_Y_k;
        }

        // 4. Calculate the expected return (E).
        // Bobby bets 1 unit.
        // If he wins (prob P_win), he gets W units (net gain W-1).
        // If he loses (prob 1 - P_win), he loses 1 unit (net gain -1).
        // Expected net gain E_net = P_win * (W - 1) + (1 - P_win) * (-1)
        // E_net = P_win * W - P_win - 1 + P_win
        // E_net = P_win * W - 1.
        
        // The problem asks if his expected return is greater than his original bet (1 unit).
        // Expected return E_return = P_win * W + (1 - P_win) * 0 = P_win * W.
        // Bobby takes the bet if E_return > 1.
        // P_win * W > 1.
        
        long double E_return = P_win * W;

        // 5. Output the result.
        if (E_return > 1.0) {
            cout << "yes\n";
        } else {
            cout << "no\n";
        }
    }
}

int main() {
    solve();
    return 0;
}