#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000100
#define SQRT 1515
#define LENGTH 20

int result[MAX];
int pw[MAX][LENGTH + 3];

int gcd(int a, int b) {
    while (1) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (a > b) a %= b;
        else b %= a;
    }
}

int getSum(int p, int q, int k) {
    long long res = 0;
    for (int i = 0; i <= k; i++) {
        res += (long long)pw[p][i] * pw[q][k - i];
        if (res >= MAX) return MAX;
    }
    return (int)res;
}

void prepare(void) {
    for (int i = 1; i < MAX; i++) {
        pw[i][0] = 1;
        for (int j = 1; j <= LENGTH; j++) {
            long long val = (long long)pw[i][j - 1] * i;
            pw[i][j] = val < MAX ? (int)val : MAX;
        }
    }

    int numPair = 0;
    for (int k = 2; k <= LENGTH; k++) {
        for (int q = 1; q <= SQRT; q++) {
            if (pw[q][k] >= MAX) break;
            for (int p = q + 1; p <= SQRT; p++) {
                int sum = getSum(p, q, k);
                if (sum >= MAX) break;
                if (gcd(p, q) > 1) continue;
                numPair++;
                result[sum]++;
            }
        }
    }
    
    int cnt = 0;
    for (int i = 1; i < MAX; i++) {
        if (result[i] > 0) cnt++;
    }
    fprintf(stderr, "%d\n", cnt);
    fprintf(stderr, "%d\n", numPair);
    
    for (int i = MAX - 1; i >= 1; i--) {
        for (int j = 2 * i; j < MAX; j += i) {
            result[j] += result[i];
        }
    }
}

int solve(int n) {
    if (n < 3) return 1;
    int numOne = 1;
    int numTwo = n % 2 == 0 ? n / 2 - 1 : n / 2;
    return numOne + numTwo + result[n];
}

int main(void) {
    prepare();
    int input;
    scanf("%d", &input);
    while (scanf("%d", &input) == 1) {
        printf("%d ", solve(input));
    }
    printf("\n");
    return 0;
}