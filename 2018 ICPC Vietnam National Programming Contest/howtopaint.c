#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MOD 100003
#define MAXN 1005

long long numerator = 1, denominator = 1, base = 0;
int m, n;
int a[MAXN], b[MAXN];
int filled[MAXN][MAXN];
int ups[MAXN][MAXN], rights[MAXN][MAXN];

void update_hook(int* w, int size) {
    assert(w[0] > 0);
    for (int i = 1; i < size; i++) {
        assert(w[i] <= w[i - 1]);
    }
    
    memset(filled, 0, sizeof(filled));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < w[i]; j++) {
            filled[i][j] = 1;
        }
    }
    
    memset(ups, 0, sizeof(ups));
    memset(rights, 0, sizeof(rights));
    
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            if (filled[i][j]) {
                ups[i][j] = (filled[i + 1][j]) ? (1 + ups[i + 1][j]) : 1;
                rights[i][j] = (filled[i][j + 1]) ? (1 + rights[i][j + 1]) : 1;
                int hook = ups[i][j] + rights[i][j] - 1;
                denominator = (denominator * hook) % MOD;
            }
        }
    }
}

void multiply(int x) {
    while (x % MOD == 0) {
        base++;
        x /= MOD;
    }
    numerator = (numerator * x) % MOD;
}

int compare_desc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    scanf("%d %d", &m, &n);
    assert(0 < m && m <= 1000);
    assert(0 < n && n <= 1000);
    
    int p = 0, q = 0;
    for (int i = 0; i < m; i++) {
        scanf("%d", &a[i]);
        assert(a[i] <= n);
        b[i] = n - a[i];
        p += a[i];
        q += b[i];
    }
    
    qsort(b, m, sizeof(int), compare_desc);
    
    update_hook(a, m);
    update_hook(b, m);
    
    for (int i = 1; i <= p + q - 2; i++) {
        multiply(i);
    }
    multiply(p);
    multiply(q);
    
    for (int i = 0; i < MOD - 2; i++) {
        numerator = (numerator * denominator) % MOD;
    }
    
    printf("%lld %lld\n", base, numerator);
    return 0;
}