// O(n^4)
import java.util.*;

public class spaceinvaders {
  public static void main(String[] args) {
    int[] A = new int[300];
    int[] B = new int[300];
    int[] H = new int[300];
    int[] TEMP = new int[300 + 2];
    int[][] DP = new int[300 + 2][300 + 2];
    
    Scanner in = new Scanner(System.in);
    int Z = in.nextInt();
    while (Z-- > 0) {
      int n = in.nextInt();
      for (int i = 0; i < n; ++i) {
        A[i] = in.nextInt();
        B[i] = in.nextInt();
        H[i] = in.nextInt();
        TEMP[i] = A[i];
      }
      for (int i = 0; i < n; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j)
          if (TEMP[j] <= A[i])
            ++count;
        A[i] = count;
        count = 0;
        for (int j = 0; j < n; ++j)
          if (TEMP[j] <= B[i])
            ++count;
        B[i] = count;
      }
      DP = new int[n + 2][n + 2];
      for (int len = 1; len < n + 2; ++len) {
        for (int from = 0; from + len < n + 2; ++from) {
          int to = from + len;
          for (int k = from + 1; k < to; ++k)
            TEMP[k] = 0;
          boolean any = false;
          for (int i = 0; i < n; ++i) {
            if (A[i] > from && B[i] < to) {
              for (int j = A[i]; j <= B[i]; ++j)
                TEMP[j] = Math.max(TEMP[j], H[i]);
              any = true;
            }
          }
          if (!any) {
            DP[from][to] = 0;
            continue;
          }
          DP[from][to] = (int)1e9;
          for (int k = from + 1; k < to; ++k)
            DP[from][to] = Math.min(DP[from][to], DP[from][k] + DP[k][to] + TEMP[k]);
        }
      }
      System.out.println(DP[0][n + 1]);
    }
  }
}