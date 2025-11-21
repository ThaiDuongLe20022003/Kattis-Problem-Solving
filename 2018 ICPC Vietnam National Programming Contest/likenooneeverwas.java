import java.util.*;

class Edge {
    int u, v;
    long cap, flow;
    Edge(int u, int v, long cap) {
        this.u = u;
        this.v = v;
        this.cap = cap;
        this.flow = 0;
    }
}

class Dinic {
    int N;
    List<Edge> E;
    List<Integer>[] g;
    int[] d, pt;

    @SuppressWarnings("unchecked")
    Dinic(int N) {
        this.N = N;
        E = new ArrayList<>();
        g = new ArrayList[N];
        for (int i = 0; i < N; i++) g[i] = new ArrayList<>();
        d = new int[N];
        pt = new int[N];
    }

    void addEdge(int u, int v, long cap) {
        if (u != v) {
            E.add(new Edge(u, v, cap));
            g[u].add(E.size() - 1);
            E.add(new Edge(v, u, 0));
            g[v].add(E.size() - 1);
        }
    }

    boolean BFS(int S, int T) {
        Queue<Integer> q = new LinkedList<>();
        q.add(S);
        Arrays.fill(d, N + 1);
        d[S] = 0;
        while (!q.isEmpty()) {
            int u = q.poll();
            if (u == T) break;
            for (int k : g[u]) {
                Edge e = E.get(k);
                if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
                    d[e.v] = d[e.u] + 1;
                    q.add(e.v);
                }
            }
        }
        return d[T] != N + 1;
    }

    long DFS(int u, int T, long flow) {
        if (u == T || flow == 0) return flow;
        for (; pt[u] < g[u].size(); ++pt[u]) {
            int k = g[u].get(pt[u]);
            Edge e = E.get(k);
            Edge oe = E.get(k ^ 1);
            if (d[e.v] == d[e.u] + 1) {
                long amt = e.cap - e.flow;
                if (flow != -1 && amt > flow) amt = flow;
                long pushed = DFS(e.v, T, amt);
                if (pushed > 0) {
                    e.flow += pushed;
                    oe.flow -= pushed;
                    return pushed;
                }
            }
        }
        return 0;
    }

    long maxFlow(int S, int T) {
        long total = 0;
        while (BFS(S, T)) {
            Arrays.fill(pt, 0);
            long flow;
            while ((flow = DFS(S, T, -1)) > 0)
                total += flow;
        }
        return total;
    }
}

public class Main {
    static final int MAXN = 10010;
    static final int MAXL = 20;
    static final long INF = (long)1e15;

    static boolean isPrime(int x) {
        for (int i = 2; i * i <= x; i++)
            if (x % i == 0) return false;
        return true;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int[] V = new int[MAXN], C = new int[MAXN];
        for (int i = 1; i <= n; i++) V[i] = sc.nextInt();
        for (int i = 1; i <= n; i++) C[i] = sc.nextInt();

        int[][] id = new int[MAXN][MAXL];
        int n_node = n + 1;
        int np = 0;

        for (int i = 2; i <= n; i++) {
            if (isPrime(i)) {
                np++;
                int j = i;
                id[i][0] = 0;
                while (j <= n) {
                    id[i][0]++;
                    id[i][id[i][0]] = n_node;
                    n_node++;
                    j *= i;
                }
            }
        }
        n_node++;

        Dinic f = new Dinic(n_node);
        int X = 10001;

        for (int i = 2; i <= n; i++) {
            if (isPrime(i)) {
                int k = id[i][0];
                f.addEdge(0, id[i][1], 0 + X);
                for (int j = 1; j <= k; j++) {
                    int cost = j * j * C[i];
                    int target = (j < k) ? id[i][j + 1] : (n_node - 1);
                    f.addEdge(id[i][j], target, cost + X);
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            f.addEdge(0, i, 0 + X);
            f.addEdge(i, n_node - 1, -V[i] + X);

            int ii = i;
            for (int j = 2; j <= ii; j++) {
                if (ii % j == 0) {
                    int cnt = 0;
                    while (ii % j == 0) {
                        cnt++;
                        ii /= j;
                    }
                    f.addEdge(i, id[j][cnt], INF);
                }
            }
        }

        long res = -f.maxFlow(0, n_node - 1) + (long)X * (n + np);
        System.out.println(res);
    }
}