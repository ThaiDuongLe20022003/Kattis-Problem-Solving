import java.util.*;
import java.util.Arrays;

public class howtopaint {
    static final int MOD = 100003;
    static final int MAXN = 1005;
    
    static long numerator = 1, denominator = 1, base = 0;
    static int m, n;
    
    static void updateHook(int[] w) {
        assert w[0] > 0;
        for (int i = 1; i < w.length; i++) {
            assert w[i] <= w[i - 1];
        }
        
        boolean[][] filled = new boolean[MAXN][MAXN];
        int[][] ups = new int[MAXN][MAXN];
        int[][] rights = new int[MAXN][MAXN];
        
        for (int i = 0; i < w.length; i++) {
            for (int j = 0; j < w[i]; j++) {
                filled[i][j] = true;
            }
        }
        
        for (int i = m - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (filled[i][j]) {
                    ups[i][j] = (i + 1 < m && filled[i + 1][j]) ? (1 + ups[i + 1][j]) : 1;
                    rights[i][j] = (j + 1 < n && filled[i][j + 1]) ? (1 + rights[i][j + 1]) : 1;
                    int hook = ups[i][j] + rights[i][j] - 1;
                    denominator = (denominator * hook) % MOD;
                }
            }
        }
    }
    
    static void multiply(int x) {
        while (x % MOD == 0) {
            base++;
            x /= MOD;
        }
        numerator = (numerator * x) % MOD;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        m = scanner.nextInt();
        n = scanner.nextInt();
        assert 0 < m && m <= 1000;
        assert 0 < n && n <= 1000;
        
        int[] a = new int[m];
        int[] b = new int[m];
        int p = 0, q = 0;
        
        for (int i = 0; i < m; i++) {
            a[i] = scanner.nextInt();
            assert a[i] <= n;
            b[i] = n - a[i];
            p += a[i];
            q += b[i];
        }
        
        Integer[] bInteger = new Integer[m];
        for (int i = 0; i < m; i++) {
            bInteger[i] = b[i];
        }
        Arrays.sort(bInteger, Collections.reverseOrder());
        for (int i = 0; i < m; i++) {
            b[i] = bInteger[i];
        }
        
        updateHook(a);
        updateHook(b);
        
        for (int i = 1; i <= p + q - 2; i++) {
            multiply(i);
        }
        multiply(p);
        multiply(q);
        
        for (int i = 0; i < MOD - 2; i++) {
            numerator = (numerator * denominator) % MOD;
        }
        
        System.out.println(base + " " + numerator);
    }
}