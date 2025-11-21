using System;
using System.Collections.Generic;

class Program {
    const long MOD = 1000000007L;
    const long INF = 1L << 60;

    static long ModInverse(long a, long b = MOD) {
        return 1 < a ? b - ModInverse(b % a, a) * b / a : 1;
    }

    static void Clean(ref long n) {
        while (n < MOD) n += MOD;
        n %= MOD;
    }

    static void Main() {
        long n = long.Parse(Console.ReadLine());

        long[][] memo = new long[n + 1][];
        for (int i = 0; i <= n; i++) {
            memo[i] = new long[n + 1];
        }

        Console.WriteLine("1 1 1");
        string[] input = Console.ReadLine().Split();
        long t1 = long.Parse(input[0]);
        long t2 = long.Parse(input[1]);
        memo[1][1] = t2;

        List<long> ans = new List<long>();
        ans.Add(t2);

        for (long i = 2; i <= n; i++) {
            Console.WriteLine($"1 1 {i}");
            input = Console.ReadLine().Split();
            t1 = long.Parse(input[0]);
            t2 = long.Parse(input[1]);

            long val;

            if (t1 == 1) {
                val = t2 - memo[i - 1][1];
                Clean(ref val);
            } else if (t1 == i) {
                val = t2 * ModInverse(memo[i - 1][i - 1]);
                Clean(ref val);
            } else {
                val = (t2 - memo[i - 1][t1]);
                Clean(ref val);
                val *= ModInverse(memo[i - 1][t1 - 1]);
                Clean(ref val);
            }

            for (int j = 1; j <= i; j++) {
                if (j == 1) {
                    memo[i][j] = memo[i - 1][j] + val;
                    Clean(ref memo[i][j]);
                } else if (j == i) {
                    memo[i][j] = memo[i - 1][j - 1] * val;
                    Clean(ref memo[i][j]);
                } else {
                    memo[i][j] = memo[i - 1][j] + memo[i - 1][j - 1] * val;
                    Clean(ref memo[i][j]);
                }
            }

            ans.Add(val);
        }

        Console.Write("2 ");
        foreach (long num in ans) {
            Console.Write(num + " ");
        }
        Console.WriteLine();
    }
}