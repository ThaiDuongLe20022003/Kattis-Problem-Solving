import java.io.*;
import java.util.*;

public class virussynthesis {
  static final int NIL = -1;
  static final int MAXN = 100000;
  static final int UPLINKS = 20;

  static String dna;
  static int[] manacher = new int[MAXN];
  static int[] ptr = new int[MAXN];
  static int next_node;
  static int[][] uplink = new int[MAXN][UPLINKS];
  static int[] depth = new int[MAXN];
  static int[] center = new int[MAXN];
  static int[] dp = new int[MAXN];
  static TreeSet<Integer> tree = new TreeSet<Integer>();

  static int nextNode(int parent) {
    uplink[next_node][0] = (parent == NIL) ? next_node : parent;
    for (int i = 1; i < UPLINKS; ++i) 
      uplink[next_node][i] = uplink[uplink[next_node][i - 1]][i - 1];
    depth[next_node] = (parent == NIL) ? 0 : (1 + depth[parent]);
    return next_node++;
  }

  static int alphaToIndex(char c) {
    if (c == 'A')
      return 0;
    else if (c == 'C')
      return 1;
    else if (c == 'G')
      return 2;
    else  // c == 'T'
      return 3;
  }

  static int goUp(int node, int levels) {
    assert levels >= 0;
    int i = 0;
    while (levels > 0) {
      if (levels % 2 == 1)
        node = uplink[node][i];
      ++i;
      levels /= 2;
    }
    return node;
  }

  public static void main(String[] args) throws Throwable {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    int Z = Integer.parseInt(in.readLine());
    while (Z-- > 0) {
      dna = in.readLine();
      next_node = 0;
      int root = nextNode(NIL);
      int n = dna.length();
      int green = 0;
      manacher[0] = 0;
      ptr[0] = root;
      for (int i = 1; i < n; ++i) {
        manacher[i] = 0;
        ptr[i] = root;
        if (2 * green - i >= 0) {
          manacher[i] = 
            Math.min(
                manacher[2 * green - i], 
                Math.max(manacher[green] + green - i, 0));
          ptr[i] = goUp(ptr[2 * green - i], manacher[2 * green - i] - manacher[i]);
        }
        while (i >= manacher[i] + 1 &&
            i + manacher[i] < n &&
            dna.charAt(i + manacher[i]) == dna.charAt(i - manacher[i] - 1)) {
          manacher[i]++;
          green = i;
          ptr[i] = nextNode(ptr[i]);
          center[ptr[i]] = i;
        }
        if (manacher[i] > 0)
          tree.add(i);
      }
      dp[0] = 0;
      for (int i = 1; i < next_node; ++i) {
        dp[i] = 1 + dp[uplink[i][0]];
        if (depth[i] <= 1) continue;
        int interesting_center;
        while (true) {
          Integer interesting_center_object = tree.ceiling(center[i] + (1 + depth[i]) / 2);
          if (interesting_center_object == null) {
            interesting_center = -1;
            break;
          }
          interesting_center = interesting_center_object;
          if (interesting_center + manacher[interesting_center] < center[i] + depth[i])
            tree.remove(interesting_center);
          else
            break;
        }
        if (interesting_center == -1)
          continue;
        if (interesting_center >= center[i] + depth[i])
          continue;
        int interesting_node = goUp(
            ptr[interesting_center],
            interesting_center + manacher[interesting_center] -
            (center[i] + depth[i]));
        dp[i] = Math.min(dp[i], depth[i] - 2 * depth[interesting_node] + dp[interesting_node] + 1);
      }
      tree.clear();
      int solution = n;
      for (int i = 1; i < next_node; ++i)
        solution = Math.min(solution, n - (2 * depth[i]) + dp[i] + 1);
      System.out.println(solution);
    }
  }
}