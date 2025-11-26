#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool win[501][501];

int main() {
    // Precompute win states
    for (int i = 1; i <= 500; ++i) {
        for (int j = 1; j <= 500; ++j) {
            win[i][j] = false;
            
            for (int k = 1; k < j; ++k) {
                win[i][j] = win[i][j] || (!win[k][i] && !win[j - k][i]);
            }
        }
    }

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int b, d;
        char s[10];
        scanf("%d %d %s", &b, &d, s);

        printf("%s ", s);
        if (s[0] == 'H') {
            printf(win[b][d] ? "can win\n" : "cannot win\n");
        } else {
            printf(win[d][b] ? "can win\n" : "cannot win\n");
        }
    }

    return 0;
}