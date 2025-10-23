// O(n^2 + n*2^deg)

import java.io.*;

public class parades {
  static final int N = 1000;
  static final int D = 10;

  static int n;
  static boolean[][] graph = new boolean[N][N];
  static boolean[][] pairs = new boolean[N][N];
  static int[][] up = new int[N][N];
  static int[] up_size = new int[N];
  static int result;
  static boolean[][] local = new boolean[D][D];
  static int[] matching = new int[1 << D];
  static int[] lowbit = new int[1 << D];
  static int[] sons = new int[N];
  static int sons_size;

  static void dfs(int u, int f) {
    for (int v = 0; v < n; ++v) {
      if (graph[u][v] && v != f) {
        dfs(v, u);
      }
    }
    sons_size = 0;
    for (int v = 0; v < n; ++v) {
      if (graph[u][v] && v != f) {
        sons[sons_size++] = v;
      }
    }
    for (int i = 0; i < sons_size; ++i) {
      for (int k = 0; k < up_size[sons[i]]; ++k) {
        int a = up[sons[i]][k];
        if (pairs[u][a]) {
          result++;
          up_size[sons[i]] = 0;
          break;
        }
      }
    }

    for (int i = 0; i < sons_size; ++i) {
      for (int j = i + 1; j < sons_size; ++j) {
        local[i][j] = false;
        for (int k = 0; k < up_size[sons[i]]; ++k)
          for (int l = 0; l < up_size[sons[j]]; ++l)
            if (pairs[up[sons[i]][k]][up[sons[j]][l]])
              local[i][j] = true;
      }
    }

    matching[0] = 0;
    for (int m = 1; m < (1 << sons_size); ++m) {
      int a = lowbit[m];
      matching[m] = matching[m - (1 << a)];
      for (int b = a + 1; b < sons_size; ++b) {
        if (((m >> b) & 1) > 0 && local[a][b])
          matching[m] = Math.max(matching[m], 1 + matching[m - (1 << a) - (1 << b)]);
      }
    }
    result += matching[(1 << sons_size) - 1];
    up_size[u] = 1;
    up[u][0] = u;
    for (int i = 0; i < sons_size; ++i)
      if (matching[(1 << sons_size) - 1] == 
          matching[(1 << sons_size) - 1 - (1 << i)])
        for (int k = 0; k < up_size[sons[i]]; ++k)
          up[u][up_size[u]++] = up[sons[i]][k];
  }

  public static void main(String[] args) throws IOException {
    for (int i = 1; i < (1 << D); ++i)
      lowbit[i] = (i & 1) > 0 ? 0 : (1 + lowbit[i >> 1]);

    // Scanner in = new Scanner(System.in);
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    int Z = Integer.parseInt(in.readLine());
    while (Z-- > 0) {
      n = Integer.parseInt(in.readLine());
      for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
          graph[i][j] = pairs[i][j] = false;
      for (int i = 0; i < n - 1; ++i) {
        String[] temp = in.readLine().split(" ");
        int a = Integer.parseInt(temp[0]) - 1;
        int b = Integer.parseInt(temp[1]) - 1;
        graph[a][b] = graph[b][a] = true;
      }
      int m = Integer.parseInt(in.readLine());
      while (m-- > 0) {
        String[] temp = in.readLine().split(" ");
        int a = Integer.parseInt(temp[0]) - 1;
        int b = Integer.parseInt(temp[1]) - 1;
        pairs[a][b] = pairs[b][a] = true;
      }
      result = 0;
      dfs(0, -1);
      System.out.println(result);
    }
  }
}