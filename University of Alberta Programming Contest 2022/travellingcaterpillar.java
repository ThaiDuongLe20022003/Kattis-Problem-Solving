import java.util.*;

public class travellingcaterpillar {
    static int n, k;
    static List<Pair<Integer, Integer>>[] adj;
    static boolean[] mark;

    static class Pair<A, B> {
        A first;
        B second;

        Pair(A first, B second) {
            this.first = first;
            this.second = second;
        }
    }

    @SuppressWarnings("unchecked")
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        k = scanner.nextInt();
        adj = new List[n];
        mark = new boolean[n];

        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }

        for (int i = 0; i < n - 1; i++) {
            int s = scanner.nextInt();
            int t = scanner.nextInt();
            int d = scanner.nextInt();
            adj[s].add(new Pair<>(t, d));
        }

        for (int i = 0; i < k; i++) {
            int j = scanner.nextInt();
            mark[j] = true;
        }

        Pair<Boolean, Long> x = dfs(0);
        System.out.println(x.first ? x.second : 0);
        scanner.close();
    }

    static Pair<Boolean, Long> dfs(int v) {
        if (adj[v].size() == 0)
            return new Pair<>(mark[v], 0L);

        long d = 0;
        boolean any = false;
        for (Pair<Integer, Integer> p : adj[v]) {
            Pair<Boolean, Long> c = dfs(p.first);
            d += c.first ? c.second + 2 * p.second : 0;
            any |= c.first;
        }
        return new Pair<>(any, d);
    }
}