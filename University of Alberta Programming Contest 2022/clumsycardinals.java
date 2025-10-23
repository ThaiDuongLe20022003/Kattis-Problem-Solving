import java.util.*;

public class clumsycardinals {
    static int[] uf;
    static Map<Integer, Integer> UD, DD;

    static int find(int u) {
        if (uf[u] != u) uf[u] = find(uf[u]);
        return uf[u];
    }

    static boolean merge(int u, int v) {
        int up = find(u), vp = find(v);
        if (up != vp) {
            uf[up] = vp;
            return true;
        }
        return false;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        uf = new int[n];
        UD = new HashMap<>();
        DD = new HashMap<>();

        for (int i = 0; i < n; ++i) {
            uf[i] = i;
        }

        int cnt = 0;
        for (int u = 0; u < n; ++u) {
            int r = scanner.nextInt();
            int c = scanner.nextInt();
            for (int i = -1; i <= 1; ++i) {
                if (UD.containsKey(r + c + i) && merge(u, UD.get(r + c + i))) {
                    cnt++;
                }
                if (DD.containsKey(r - c + i) && merge(u, DD.get(r - c + i))) {
                    cnt++;
                }
            }
            UD.put(r + c, u);
            DD.put(r - c, u);
        }
        System.out.println(n - cnt);
    }
}