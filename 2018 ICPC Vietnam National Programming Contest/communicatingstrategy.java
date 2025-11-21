import java.util.*;

public class communicatingstrategy {
    static final long MOD = 1000000007L;
    static final long INF = 1L << 60;

    static long modInverse(long a, long b) {
        return 1 < a ? b - modInverse(b % a, a) * b / a : 1;
    }

    static long modInverse(long a) {
        return modInverse(a, MOD);
    }

    static void clean(long[] n) {
        while (n[0] < MOD) n[0] += MOD;
        n[0] %= MOD;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        long n = scanner.nextLong();

        long[][] memo = new long[(int)(n + 1)][(int)(n + 1)];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(memo[i], 0);
        }

        System.out.println("1 1 1");
        System.out.flush();
        long t1 = scanner.nextLong();
        long t2 = scanner.nextLong();
        memo[1][1] = t2;

        List<Long> ans = new ArrayList<>();
        ans.add(t2);

        for (long i = 2; i <= n; i++) {
            System.out.println("1 1 " + i);
            System.out.flush();
            t1 = scanner.nextLong();
            t2 = scanner.nextLong();

            long val;

            if (t1 == 1) {
                val = t2 - memo[(int)(i - 1)][1];
                long[] valRef = {val};
                clean(valRef);
                val = valRef[0];
            } else if (t1 == i) {
                val = t2 * modInverse(memo[(int)(i - 1)][(int)(i - 1)]);
                long[] valRef = {val};
                clean(valRef);
                val = valRef[0];
            } else {
                val = (t2 - memo[(int)(i - 1)][(int)t1]);
                long[] valRef = {val};
                clean(valRef);
                val = valRef[0];
                val *= modInverse(memo[(int)(i - 1)][(int)(t1 - 1)]);
                valRef[0] = val;
                clean(valRef);
                val = valRef[0];
            }

            for (int j = 1; j <= i; j++) {
                if (j == 1) {
                    memo[(int)i][j] = memo[(int)(i - 1)][j] + val;
                    long[] temp = {memo[(int)i][j]};
                    clean(temp);
                    memo[(int)i][j] = temp[0];
                } else if (j == i) {
                    memo[(int)i][j] = memo[(int)(i - 1)][j - 1] * val;
                    long[] temp = {memo[(int)i][j]};
                    clean(temp);
                    memo[(int)i][j] = temp[0];
                } else {
                    memo[(int)i][j] = memo[(int)(i - 1)][j] + memo[(int)(i - 1)][j - 1] * val;
                    long[] temp = {memo[(int)i][j]};
                    clean(temp);
                    memo[(int)i][j] = temp[0];
                }
            }

            ans.add(val);
        }

        System.out.print("2 ");
        for (long num : ans) {
            System.out.print(num + " ");
        }
        System.out.println();
        System.out.flush();
    }
}