#include <stdio.h>
#include <math.h>

// Function to compute nCr (n choose r)
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

int main() {
    int N_cases;
    if (scanf("%d", &N_cases) != 1) return 0;

    while (N_cases--) {
        int R, S, X, Y, W;
        if (scanf("%d %d %d %d %d", &R, &S, &X, &Y, &W) != 5) return 0;

        // Calculate probability of a single successful roll
        long double p_success = 0.0;
        if (R <= S) {
            p_success = (long double)(S - R + 1) / S;
        }

        long double p_failure = 1.0 - p_success;

        // Calculate probability of winning the bet
        long double P_win = 0.0;
        for (int k = X; k <= Y; ++k) {
            long double nCk = combinations(Y, k);
            long double p_succ_k = powl(p_success, k);
            long double p_fail_Y_k = powl(p_failure, Y - k);
            P_win += nCk * p_succ_k * p_fail_Y_k;
        }

        // Calculate expected return and output result
        long double E_return = P_win * W;
        if (E_return > 1.0) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    }

    return 0;
}