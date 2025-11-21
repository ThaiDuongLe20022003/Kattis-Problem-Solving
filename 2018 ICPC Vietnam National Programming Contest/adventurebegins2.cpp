#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7;

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long mod_inverse(long long a) {
    return mod_pow(a, MOD - 2, MOD);
}

class SegmentTree {
private:
    vector<long long> tree, lazy;
    int n;
    
    void push(int node, int start, int end) {
        if (lazy[node] != 0) {
            tree[node] = (tree[node] + lazy[node] * (end - start + 1)) % MOD;
            if (start != end) {
                lazy[2*node] = (lazy[2*node] + lazy[node]) % MOD;
                lazy[2*node+1] = (lazy[2*node+1] + lazy[node]) % MOD;
            }
            lazy[node] = 0;
        }
    }
    
    void update_range(int node, int start, int end, int l, int r, long long val) {
        push(node, start, end);
        if (start > r || end < l) return;
        
        if (start >= l && end <= r) {
            lazy[node] = (lazy[node] + val) % MOD;
            push(node, start, end);
            return;
        }
        
        int mid = (start + end) / 2;
        update_range(2*node, start, mid, l, r, val);
        update_range(2*node+1, mid+1, end, l, r, val);
        
        push(2*node, start, mid);
        push(2*node+1, mid+1, end);
        tree[node] = (tree[2*node] + tree[2*node+1]) % MOD;
    }
    
    long long query_range(int node, int start, int end, int l, int r) {
        if (start > r || end < l) return 0;
        push(node, start, end);
        
        if (start >= l && end <= r) return tree[node];
        
        int mid = (start + end) / 2;
        long long left_sum = query_range(2*node, start, mid, l, r);
        long long right_sum = query_range(2*node+1, mid+1, end, l, r);
        return (left_sum + right_sum) % MOD;
    }
    
public:
    SegmentTree(int size) : n(size) {
        tree.resize(4 * n, 0);
        lazy.resize(4 * n, 0);
    }
    
    void update(int l, int r, long long val) {
        update_range(1, 1, n, l, r, val);
    }
    
    long long query(int l, int r) {
        return query_range(1, 1, n, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    long long S = 0;
    SegmentTree seg(n);
    
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int u, v;
            cin >> u >> v;
            
            long long q_inv = mod_inverse(v - u + 1);
            long long sum_xi = seg.query(u, v);
            
            S = (S + 2LL * q_inv % MOD * sum_xi % MOD + 1) % MOD;
            seg.update(u, v, q_inv);
        } else {
            cout << S << "\n";
        }
    }
    
    return 0;
}