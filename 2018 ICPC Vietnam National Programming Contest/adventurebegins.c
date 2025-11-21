#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

// Modular arithmetic functions
int mul(int a, int b) {
    return (int)(((ll)a * b) % MOD);
}

int power(int x, int n) {
    int ans = 1;
    while (n) {
        if (n & 1)
            ans = mul(ans, x);
        x = mul(x, x);
        n >>= 1;
    }
    return ans;
}

int inv(int x) {
    return power(x, MOD - 2);
}

// Segment Tree Node structure
typedef struct {
    int sum; // sum of E(a_i) for the range
    int val; // lazy value (amount to add to E(a_i))
} Node;

Node *t;
int N_GLOBAL;

void propagate(int id, int l, int r) {
    int x = t[id].val;
    if (x != 0) {
        int m = (l + r) / 2;
        
        // Update sum for left child: sum += (length) * x
        t[2 * id].sum = (t[2 * id].sum + (ll)(m - l + 1) * x) % MOD;
        // Update lazy value for left child: val += x
        t[2 * id].val = (t[2 * id].val + x) % MOD;
        
        // Update sum for right child: sum += (length) * x
        t[2 * id + 1].sum = (t[2 * id + 1].sum + (ll)(r - m) * x) % MOD;
        // Update lazy value for right child: val += x
        t[2 * id + 1].val = (t[2 * id + 1].val + x) % MOD;
        
        // Clear lazy value
        t[id].val = 0;
    }
}

void update(int id, int l, int r, const int i, const int j, const int x) {
    if (i > r || j < l) return;
    if (i <= l && r <= j) {
        // Update sum for the current node: sum += (length) * x
        t[id].sum = (t[id].sum + (ll)(r - l + 1) * x) % MOD;
        // Update lazy value for the current node: val += x
        t[id].val = (t[id].val + x) % MOD;
        return;
    }

    propagate(id, l, r);

    int m = (l + r) / 2;
    update(2 * id, l, m, i, j, x);
    update(2 * id + 1, m + 1, r, i, j, x);
    // Recalculate sum from children
    t[id].sum = (t[2 * id].sum + t[2 * id + 1].sum) % MOD;
}

int query(int id, int l, int r, const int i, const int j) {
    if (i > r || j < l) return 0;
    if (i <= l && r <= j)
        return t[id].sum;

    propagate(id, l, r);

    int m = (l + r) / 2;
    // Sum of queries from children
    return (query(2 * id, l, m, i, j) + query(2 * id + 1, m + 1, r, i, j)) % MOD;
}

int main() {
    int n, q;
    if (scanf("%d%d", &n, &q) != 2) return 0;
    N_GLOBAL = n;

    // Segment tree size: 4*N is a safe upper bound
    t = (Node *)calloc(4 * n + 1, sizeof(Node));
    if (t == NULL) return 1; // Memory allocation failed

    int ans = 0; // ans stores E(A)
    for (int k = 1; k <= q; ++k) {
        int type;
        if (scanf("%d", &type) != 1) break;

        if (type == 1) {
            int l, r;
            if (scanf("%d%d", &l, &r) != 2) break;

            // Length of the range [l, r]
            int len = r - l + 1;
            // q = inv(len) = (v-u+1)^-1 mod MOD
            int x = inv(len); 
            
            // The formula is S' = S + 2q * sum E(a_i) + 1
            
            // 1. Add the +1 term
            ans = (ans + 1) % MOD;
            
            // 2. Add the + 2q * sum E(a_i) term
            int sum_E_ai = query(1, 1, n, l, r);
            int term2 = mul(2, mul(x, sum_E_ai));
            ans = (ans + term2) % MOD;
            
            // 3. Update E(a_i) += q for i in [l, r]
            update(1, 1, n, l, r, x);
            
        } else {
            // Type 2: Print E(A)
            printf("%d\n", ans);
        }
    }

    free(t);
    return 0;
}