using System;
using System.Linq;

class Program {
    const int MOD = 100003;
    const int MAXN = 1005;
    
    static long numerator = 1, denominator = 1, baseVal = 0;
    static int m, n;
    
    static void UpdateHook(int[] w) {
        System.Diagnostics.Debug.Assert(w[0] > 0);
        for (int i = 1; i < w.Length; i++) {
            System.Diagnostics.Debug.Assert(w[i] <= w[i - 1]);
        }
        
        bool[,] filled = new bool[MAXN, MAXN];
        int[,] ups = new int[MAXN, MAXN];
        int[,] rights = new int[MAXN, MAXN];
        
        for (int i = 0; i < w.Length; i++) {
            for (int j = 0; j < w[i]; j++) {
                filled[i, j] = true;
            }
        }
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (filled[i, j]) {
                    ups[i, j] = (i + 1 < m && filled[i + 1, j]) ? (1 + ups[i + 1, j]) : 1;
                    rights[i, j] = (j + 1 < n && filled[i, j + 1]) ? (1 + rights[i, j + 1]) : 1;
                    int hook = ups[i, j] + rights[i, j] - 1;
                    denominator = (denominator * hook) % MOD;
                }
            }
        }
    }
    
    static void Multiply(int x) {
        while (x % MOD == 0) {
            baseVal++;
            x /= MOD;
        }
        numerator = (numerator * x) % MOD;
    }
    
    static void Main() {
        string[] input = Console.ReadLine().Split();
        m = int.Parse(input[0]);
        n = int.Parse(input[1]);
        System.Diagnostics.Debug.Assert(0 < m && m <= 1000);
        System.Diagnostics.Debug.Assert(0 < n && n <= 1000);
        
        int[] a = new int[m];
        int[] b = new int[m];
        int p = 0, q = 0;
        
        input = Console.ReadLine().Split();
        for (int i = 0; i < m; i++) {
            a[i] = int.Parse(input[i]);
            System.Diagnostics.Debug.Assert(a[i] <= n);
            b[i] = n - a[i];
            p += a[i];
            q += b[i];
        }
        
        Array.Sort(b);
        Array.Reverse(b);
        
        UpdateHook(a);
        UpdateHook(b);
        
        for (int i = 1; i <= p + q - 2; i++) {
            Multiply(i);
        }
        Multiply(p);
        Multiply(q);
        
        for (int i = 0; i < MOD - 2; i++) {
            numerator = (numerator * denominator) % MOD;
        }
        
        Console.WriteLine($"{baseVal} {numerator}");
    }
}