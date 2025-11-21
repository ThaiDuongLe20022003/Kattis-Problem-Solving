import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class adventurebegins {
    private static final int MOD = 1000000007;

    private static long mul(long a, long b) {
        return (a * b) % MOD;
    }

    private static long power(long x, int n) {
        long ans = 1;
        x %= MOD;
        while (n > 0) {
            if ((n & 1) == 1)
                ans = mul(ans, x);
            x = mul(x, x);
            n >>= 1;
        }
        return ans;
    }

    private static long inv(long x) {
        return power(x, MOD - 2);
    }

    private static class Node {
        long sum; // sum of E(a_i) for the range
        long val; // lazy value (amount to add to E(a_i))
    }

    private static Node[] t;
    private static int N;

    private static void propagate(int id, int l, int r) {
        long x = t[id].val;
        if (x != 0) {
            int m = (l + r) / 2;
            
            // Update sum for left child: sum += (length) * x
            t[2 * id].sum = (t[2 * id].sum + (long)(m - l + 1) * x) % MOD;
            // Update lazy value for left child: val += x
            t[2 * id].val = (t[2 * id].val + x) % MOD;
            
            // Update sum for right child: sum += (length) * x
            t[2 * id + 1].sum = (t[2 * id + 1].sum + (long)(r - m) * x) % MOD;
            // Update lazy value for right child: val += x
            t[2 * id + 1].val = (t[2 * id + 1].val + x) % MOD;
            
            // Clear lazy value
            t[id].val = 0;
        }
    }

    private static void update(int id, int l, int r, int i, int j, long x) {
        if (i > r || j < l) return;
        if (i <= l && r <= j) {
            // Update sum for the current node: sum += (length) * x
            t[id].sum = (t[id].sum + (long)(r - l + 1) * x) % MOD;
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

    private static long query(int id, int l, int r, int i, int j) {
        if (i > r || j < l) return 0;
        if (i <= l && r <= j)
            return t[id].sum;

        propagate(id, l, r);

        int m = (l + r) / 2;
        // Sum of queries from children
        return (query(2 * id, l, m, i, j) + query(2 * id + 1, m + 1, r, i, j)) % MOD;
    }

    public static void main(String[] args) throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        StringTokenizer st = new StringTokenizer(br.readLine());

        N = Integer.parseInt(st.nextToken());
        int Q = Integer.parseInt(st.nextToken());

        // Initialize segment tree
        t = new Node[4 * N + 1];
        for (int i = 0; i <= 4 * N; i++) {
            t[i] = new Node();
            t[i].sum = 0;
            t[i].val = 0;
        }

        long ans = 0; // ans stores E(A)
        for (int k = 0; k < Q; k++) {
            String line = br.readLine();
            if (line == null) break;
            st = new StringTokenizer(line);
            int type = Integer.parseInt(st.nextToken());

            if (type == 1) {
                int l = Integer.parseInt(st.nextToken());
                int r = Integer.parseInt(st.nextToken());

                // Length of the range [l, r]
                int len = r - l + 1;
                // q = inv(len) = (v-u+1)^-1 mod MOD
                long x = inv(len);

                // The formula is S' = S + 2q * sum E(a_i) + 1

                // 1. Add the +1 term
                ans = (ans + 1) % MOD;

                // 2. Add the + 2q * sum E(a_i) term
                long sumE_ai = query(1, 1, N, l, r);
                long term2 = mul(2, mul(x, sumE_ai));
                ans = (ans + term2) % MOD;

                // 3. Update E(a_i) += q for i in [l, r]
                update(1, 1, N, l, r, x);
            } else {
                // Type 2: Print E(A)
                pw.println(ans);
            }
        }

        pw.flush();
    }
}