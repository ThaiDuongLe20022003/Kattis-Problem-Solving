import java.util.*;
import java.io.*;

public class hillnumbers {
    private static String S;
    private static long[][][][] memo;
    
    private static long dp(int pos, int prev_d, boolean is_less, boolean is_started, boolean is_falling) {
        if (pos == S.length()) {
            return is_started ? 1 : 0;
        }
        
        int less = is_less ? 1 : 0;
        int falling = is_falling ? 1 : 0;
        
        if (memo[pos][prev_d][less][falling] != -1) {
            return memo[pos][prev_d][less][falling];
        }
        
        long ans = 0;
        int upper_bound = is_less ? 9 : (S.charAt(pos) - '0');
        
        for (int d = 0; d <= upper_bound; d++) {
            if (!is_started) {
                if (d == 0) {
                    ans += dp(pos + 1, 0, true, false, false);
                } else {
                    ans += dp(pos + 1, d, is_less || (d < upper_bound), true, false);
                }
            } else {
                if (is_falling) {
                    if (d <= prev_d) {
                        ans += dp(pos + 1, d, is_less || (d < upper_bound), true, true);
                    }
                } else {
                    if (d < prev_d) {
                        ans += dp(pos + 1, d, is_less || (d < upper_bound), true, true);
                    } else {
                        ans += dp(pos + 1, d, is_less || (d < upper_bound), true, false);
                    }
                }
            }
        }
        
        memo[pos][prev_d][less][falling] = ans;
        return ans;
    }
    
    private static boolean isHillNumber(String s) {
        if (s == null || s.isEmpty()) return false;
        if (s.chars().allMatch(c -> c == '0')) return false;
        
        boolean falling = false;
        for (int i = 0; i < s.length() - 1; i++) {
            if (s.charAt(i) < s.charAt(i + 1)) {
                if (falling) return false;
            } else if (s.charAt(i) > s.charAt(i + 1)) {
                falling = true;
            }
        }
        return true;
    }
    
    private static long solve(String n_str) {
        S = n_str;
        memo = new long[20][10][2][2];
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 2; k++)
                    for (int l = 0; l < 2; l++)
                        memo[i][j][k][l] = -1;
                        
        return dp(0, 0, false, false, false);
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String n_str;
        
        while ((n_str = br.readLine()) != null && !n_str.isEmpty()) {
            if (!isHillNumber(n_str)) {
                System.out.println("-1");
            } else {
                System.out.println(solve(n_str));
            }
        }
    }
}