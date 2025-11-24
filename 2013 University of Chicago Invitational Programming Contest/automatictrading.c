#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 100010

char s[MAXN];
int N, gap;
int sa[MAXN], pos[MAXN], lcp[MAXN], tmp[MAXN];

int sufCmp(int i, int j) {
    if (pos[i] != pos[j]) return pos[i] < pos[j];
    i += gap;
    j += gap;
    return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}

int cmp(const void *a, const void *b) {
    int i = *(int*)a;
    int j = *(int*)b;
    return sufCmp(i, j) ? -1 : 1;
}

void buildSA() {
    N = strlen(s);
    for (int i = 0; i < N; ++i) {
        sa[i] = i;
        pos[i] = s[i];
    }
    for (gap = 1;; gap *= 2) {
        qsort(sa, N, sizeof(int), cmp);
        tmp[0] = 0;
        for (int i = 0; i < N - 1; ++i)
            tmp[i + 1] = tmp[i] + sufCmp(sa[i], sa[i + 1]);
        for (int i = 0; i < N; ++i) pos[sa[i]] = tmp[i];
        if (tmp[N - 1] == N - 1) break;
    }
}

void buildLCP() {
    N = strlen(s);
    for (int i = 0, k = 0; i < N; ++i) {
        if (pos[i] != 0) {
            int j = sa[pos[i] - 1];
            while (s[i + k] == s[j + k]) k++;
            lcp[pos[i]] = k;
            if (k) k--;
        }
    }
}

typedef struct {
    int **memo;
    int *logTwo;
    int maxPow;
    int n;
} SparseTable;

SparseTable* createSparseTable(int *arr, int n) {
    SparseTable *st = malloc(sizeof(SparseTable));
    st->n = n;
    
    st->logTwo = malloc((n + 1) * sizeof(int));
    st->logTwo[0] = st->logTwo[1] = 0;
    for (int i = 2; i <= n; ++i)
        st->logTwo[i] = 1 + st->logTwo[i / 2];
    
    st->maxPow = st->logTwo[n] + 1;
    st->memo = malloc(st->maxPow * sizeof(int*));
    for (int j = 0; j < st->maxPow; ++j) {
        st->memo[j] = malloc(n * sizeof(int));
        for (int i = 0; i < n; ++i) {
            if (i + (1 << j) - 1 < n) {
                if (j == 0) {
                    st->memo[j][i] = arr[i];
                } else {
                    st->memo[j][i] = (st->memo[j-1][i] < st->memo[j-1][i + (1 << (j-1))]) 
                                    ? st->memo[j-1][i] : st->memo[j-1][i + (1 << (j-1))];
                }
            }
        }
    }
    return st;
}

int query(SparseTable *st, int l, int r) {
    if (l > r) return 0;
    int j = st->logTwo[r - l + 1];
    int left = st->memo[j][l];
    int right = st->memo[j][r - (1 << j) + 1];
    return left < right ? left : right;
}

void freeSparseTable(SparseTable *st) {
    for (int j = 0; j < st->maxPow; ++j)
        free(st->memo[j]);
    free(st->memo);
    free(st->logTwo);
    free(st);
}

int main() {
    scanf("%s", s);
    buildSA();
    
    int *inv = malloc(strlen(s) * sizeof(int));
    for (int i = 0; i < strlen(s); ++i) {
        inv[sa[i]] = i;
    }
    
    buildLCP();
    
    int *temp = malloc(strlen(s) * sizeof(int));
    for (int i = 0; i < strlen(s); ++i) {
        temp[i] = lcp[i];
    }
    
    SparseTable *st = createSparseTable(temp, strlen(s));
    
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        int pos1, pos2;
        scanf("%d %d", &pos1, &pos2);
        pos1 = inv[pos1];
        pos2 = inv[pos2];
        if (pos1 > pos2) {
            int temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
        printf("%d\n", query(st, pos1 + 1, pos2));
    }
    
    free(inv);
    free(temp);
    freeSparseTable(st);
    return 0;
}