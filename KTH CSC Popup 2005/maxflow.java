import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class maxflow {
    static final int INF = 1 << 29;
    static int[][] flowEdges;
    static int[][] capacity;
    static List<Integer>[] adj;

    static boolean bfs(int s, int t, int[] parent) {
        boolean[] visited = new boolean[capacity.length];
        Queue<Integer> q = new LinkedList<>();
        q.offer(s);
        parent[s] = -1;
        visited[s] = true;

        while (!q.isEmpty()) {
            int cur = q.poll();

            for (int n : adj[cur]) {
                if (!visited[n] && capacity[cur][n] > 0) {
                    parent[n] = cur;
                    visited[n] = true;
                    q.offer(n);
                    if (n == t) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    static int maxFlow(int s, int t, int n) {
        int[] parent = new int[n];

        int maxflow = 0;
        while (bfs(s, t, parent)) {
            int flow = INF;

            for (int cur = t; cur != s; cur = parent[cur]) {
                int p = parent[cur];
                flow = Math.min(flow, capacity[p][cur]);
            }

            for (int cur = t; cur != s; cur = parent[cur]) {
                int p = parent[cur];
                flowEdges[p][cur] += flow;
                flowEdges[cur][p] -= flow;
                capacity[p][cur] -= flow;
                capacity[cur][p] += flow;
            }

            maxflow += flow;
        }
        return maxflow;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        int n = Integer.parseInt(st.nextToken());
        int m = Integer.parseInt(st.nextToken());
        int s = Integer.parseInt(st.nextToken());
        int t = Integer.parseInt(st.nextToken());

        adj = new List[n];
        capacity = new int[n][n];
        flowEdges = new int[n][n];

        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }

        for (int i = 0; i < m; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            int c = Integer.parseInt(st.nextToken());
            adj[u].add(v);
            adj[v].add(u);
            capacity[u][v] = c;
        }

        int result = maxFlow(s, t, n);
        int countEdges = 0;
        List<Map.Entry<Integer, Integer>> ans = new ArrayList<>();

        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (flowEdges[r][c] > 0) {
                    countEdges++;
                    ans.add(new AbstractMap.SimpleEntry<>(r, c));
                }
            }
        }

        System.out.println(n + " " + result + " " + countEdges);
        for (Map.Entry<Integer, Integer> e : ans) {
            int u = e.getKey();
            int v = e.getValue();
            System.out.println(u + " " + v + " " + flowEdges[u][v]);
        }
    }
}