#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL
#define INF ((long long)1 << 60)

long long modinverse(long long a, long long b) {
    return 1 < a ? b - modinverse(b % a, a) * b / a : 1;
}

void clean(long long* n) {
    while (*n < MOD) *n += MOD;
    *n %= MOD;
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long** memo = (long long**)malloc((n + 1) * sizeof(long long*));
    for (int i = 0; i <= n; i++) {
        memo[i] = (long long*)malloc((n + 1) * sizeof(long long));
        for (int j = 0; j <= n; j++) {
            memo[i][j] = 0;
        }
    }

    printf("1 1 1\n");
    fflush(stdout);
    long long t1, t2;
    scanf("%lld %lld", &t1, &t2);
    memo[1][1] = t2;

    long long* ans = (long long*)malloc(n * sizeof(long long));
    int ans_size = 0;
    ans[ans_size++] = t2;

    for (long long i = 2; i <= n; i++) {
        printf("1 1 %lld\n", i);
        fflush(stdout);
        scanf("%lld %lld", &t1, &t2);

        long long val;

        if (t1 == 1) {
            val = t2 - memo[i - 1][1];
            clean(&val);
        } else if (t1 == i) {
            val = t2 * modinverse(memo[i - 1][i - 1], MOD);
            clean(&val);
        } else {
            val = (t2 - memo[i - 1][t1]);
            clean(&val);
            val *= modinverse(memo[i - 1][t1 - 1], MOD);
            clean(&val);
        }

        for (int j = 1; j <= i; j++) {
            if (j == 1) {
                memo[i][j] = memo[i - 1][j] + val;
                clean(&memo[i][j]);
            } else if (j == i) {
                memo[i][j] = memo[i - 1][j - 1] * val;
                clean(&memo[i][j]);
            } else {
                memo[i][j] = memo[i - 1][j] + memo[i - 1][j - 1] * val;
                clean(&memo[i][j]);
            }
        }

        ans[ans_size++] = val;
    }

    printf("2 ");
    for (int i = 0; i < ans_size; i++) {
        printf("%lld ", ans[i]);
    }
    printf("\n");
    fflush(stdout);

    for (int i = 0; i <= n; i++) {
        free(memo[i]);
    }
    free(memo);
    free(ans);

    return 0;
}