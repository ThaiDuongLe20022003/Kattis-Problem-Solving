import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.Arrays;

class Edge {
    int u, v, w;

    Edge(int u, int v, int w) {
        this.u = u;
        this.v = v;
        this.w = w;
    }
}

public class shortestpath3 {
    static final long INF = 10000000;

    static List<Integer> shortestpath3(List<Edge> edges, int s, int n) {
        long[] dist = new long[n];
        Arrays.fill(dist, INF);
        dist[s] = 0;

        for (int i = 0; i < (n - 1) * 2; i++) {
            for (Edge e : edges) {
                int u = e.u;
                int v = e.v;
                int w = e.w;

                if (dist[u] != INF && dist[v] > dist[u] + w) {
                    dist[v] = i >= n - 1 ? -INF : dist[u] + w;
                }
            }
        }

        List<Integer> result = new ArrayList<>();
        for (long d : dist) {
            if (d == INF) {
                result.add(Integer.MAX_VALUE);
            } else if (d == -INF) {
                result.add(Integer.MIN_VALUE);
            } else {
                result.add((int) d);
            }
        }
        return result;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n, m, q, s;
        n = scanner.nextInt();
        m = scanner.nextInt();
        q = scanner.nextInt();
        s = scanner.nextInt();

        while (n != 0 || m != 0 || q != 0 || s != 0) {
            List<Edge> edges = new ArrayList<>();
            for (int i = 0; i < m; i++) {
                int u = scanner.nextInt();
                int v = scanner.nextInt();
                int w = scanner.nextInt();
                edges.add(new Edge(u, v, w));
            }

            List<Integer> dist = shortestpath3(edges, s, n);
            for (int i = 0; i < q; i++) {
                int x = scanner.nextInt();
                int result = dist.get(x);
                if (result == Integer.MAX_VALUE) {
                    System.out.println("Impossible");
                } else if (result == Integer.MIN_VALUE) {
                    System.out.println("-Infinity");
                } else {
                    System.out.println(result);
                }
            }

            n = scanner.nextInt();
            m = scanner.nextInt();
            q = scanner.nextInt();
            s = scanner.nextInt();
        }
    }
}