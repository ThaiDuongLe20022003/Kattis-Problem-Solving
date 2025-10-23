import java.io.*;
import java.util.*;

public class porkbarrel {

  static long[] unique(long[] array) {
    int count_unique = 1;
    for (int i = 1; i < array.length; ++i)
      if (array[i-1] < array[i])
        count_unique++;
    long[] result = new long[count_unique];
    result[0] = array[0];
    count_unique = 1;
    for (int i = 1; i < array.length; ++i)
      if (array[i-1] < array[i])
        result[count_unique++] = array[i];
    return result;
  }

  static int[] addToArray(int[] array, int element) {
    int[] result = new int[array.length + 1];
    for (int i = 0; i < array.length; ++i)
      result[i] = array[i];
    result[array.length] = element;
    return result;
  }

  static int[] removeFromArray(int[] array, int element) {
    int[] result = new int[array.length - 1];
    int i = 0;
    for (int x : array)
      if (x != element)
        result[i++] = x;
    return result;
  }

  static final int MAXNODES = 256 * 1024 + 36 * 100 * 1000;
  static int next_node;
  static int T;
  static int[] left = new int[MAXNODES];
  static int[] right = new int[MAXNODES];
  static int[] tree = new int[MAXNODES];

  static int treeInit(int n) {
    T = 1;
    while (T < n) T *= 2;
    for (int i = 0; i < T; ++i)
      left[i + T] = right[i + T] = -1;
    for (int i = T - 1; i > 0; --i) {
      left[i] = 2 * i;
      right[i] = 2 * i + 1;
    }
    for (int i = 0; i < 2 * T; ++i)
      tree[i] = 0;
    next_node = 2 * T;
    return 1;
  }

  static int treeUpdate(int tree_size, int root, int a, int val) {
    if (tree_size == 1) {
      left[next_node] = right[next_node] = -1;
      tree[next_node] = val;
      return next_node++;
    }
    if (a < tree_size / 2) {
      int new_left = treeUpdate(tree_size / 2, left[root], a, val);
      left[next_node] = new_left;
      right[next_node] = right[root];
      tree[next_node] = tree[left[next_node]] + tree[right[next_node]];
      return next_node++;
    } else {
      int new_right = treeUpdate(tree_size / 2, right[root], a - tree_size / 2, val);
      left[next_node] = left[root];
      right[next_node] = new_right;
      tree[next_node] = tree[left[next_node]] + tree[right[next_node]];
      return next_node++;
    }
  }

  static int treeUpdate(int root, int a, int val) {
    return treeUpdate(T, root, a, val);
  }

  static int treeQuery(int tree_size, int root, int a) {
    if (tree_size == 1)
      return tree[root];
    if (a < tree_size / 2)
      return treeQuery(tree_size / 2, left[root], a);
    else
      return tree[left[root]] + treeQuery(tree_size / 2, right[root], a - tree_size / 2);
  }

  static int treeQuery(int root, int a) { 
    return treeQuery(T, root, a);
  }

  public static void main(String[] args) throws IOException {
    BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    int Z = Integer.parseInt(in.readLine());
    while (Z-- > 0) {
      String[] temp;
      temp = in.readLine().split(" ");
      int n = Integer.parseInt(temp[0]);
      int m = Integer.parseInt(temp[1]);
      long[] edges = new long[m];
      for (int i = 0; i < m; ++i) {
        temp = in.readLine().split(" ");
        int x = Integer.parseInt(temp[0]) - 1;
        int y = Integer.parseInt(temp[1]) - 1;
        if (x > y) {
          int swap = x;
          x = y;
          y = swap;
        }
        int w = Integer.parseInt(temp[2]);
        edges[i] = w * (long)(1024 * 1024) + y * 1024 + x;
      }
      Arrays.sort(edges);
      edges = unique(edges);
      m = edges.length;
      int[] history = new int[m + 1];
      history[m] = treeInit(m);
      int[][] graph = new int[n][0];
      int[] queue = new int[n];
      int[] parent = new int[n];
      for (int t = m - 1; t >= 0; --t) {
        history[t] = history[t + 1];

        long edge = edges[t];
        int x = (int)(edge & (1023));
        int y = (int)((edge >> 10) & 1023);
        int w = (int)(edge >> 20);

        for (int i = 0; i < n; ++i) parent[i] = -1;
        int qbegin = 0, qend = 0;
        queue[qend++] = x;
        
        while (qbegin < qend) {
          int u = queue[qbegin++];
          if (u == y)
            break;
          for (int v_edge : graph[u]) {
            int v_node = v_edge & (1023);
            if (v_edge != parent[u]) {
              queue[qend++] = v_node;
              parent[v_node] = (v_edge >> 10) * 1024 + u;
            }
          }
        }

        if (parent[y] != -1) {
          int best_node = y;
          int best_edge = parent[y];
          for (int u = y; u != x; u = parent[u] & 1023) {
            if (parent[u] > best_edge) {
              best_node = u;
              best_edge = parent[u];
            }
          }

          graph[best_node] = removeFromArray(graph[best_node], best_edge);
          graph[best_edge & 1023] = removeFromArray(graph[best_edge & 1023], (best_edge >> 10) * 1024 + best_node);
          
          int x2 = best_node;
          int y2 = best_edge & 1023;
          int w2 = best_edge >> 10;
          if (x2 > y2) {
            int swap = x2;
            x2 = y2;
            y2 = swap;
          }
          history[t] = treeUpdate(
              history[t], 
              Arrays.binarySearch(edges, w2 * (long)(1024 * 1024) + y2 * 1024 + x2),
              0);

        }

        graph[x] = addToArray(graph[x], w * 1024 + y);
        graph[y] = addToArray(graph[y], w * 1024 + x);

        history[t] = treeUpdate(history[t], t, w);
      }
      int q = Integer.parseInt(in.readLine());
      int solution = 0;
      while (q-- > 0) {
        temp = in.readLine().split(" ");
        int lo = Integer.parseInt(temp[0]) - solution;
        int hi = Integer.parseInt(temp[1]) - solution;
        lo = Arrays.binarySearch(edges, lo * (long)(1024 * 1024));
        hi = Arrays.binarySearch(edges, (1 + hi) * (long)(1024 * 1024));
        if (lo < 0) lo = -(lo + 1);
        if (hi < 0) hi = -(hi + 1);
        if (lo >= hi) {
          solution = 0;
        } else {
          solution = treeQuery(history[lo], hi - 1);
        }
        System.out.println(solution);
      }
    }
  }
}