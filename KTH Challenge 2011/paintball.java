import java.io.*;
import java.util.*;

public class paintball {
    private static int[] par;
    private static boolean[] bol;
    private static boolean find(int j, Vector<Vector<Integer> > g) {
        if (par[j] == -1) return true;
        bol[j] = true; int di = par[j];
        for (int i = 0; i < g.get(di).size(); i++)
        {
            int u = g.get(di).get(i);
            if (!bol[u] && find(u, g))
            {
                par[u] = di;
                par[j] = -1;
                return true;
            }
        }
        return false;
    }
    private static int match(Vector<Vector<Integer> > g, int n, int m)
    {
        par = new int[m];
        Arrays.fill(par, -1);
        bol = new boolean[m];
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            Arrays.fill(bol, false);
            for (int j = 0; j < g.get(i).size(); j++)
                if (find(g.get(i).get(j), g))
                {
                    cnt++;
                    par[g.get(i).get(j)] = i;
                    break;
                }
        }
        return cnt;
    }
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        int n = sc.nextInt(), m = sc.nextInt();

        Vector<Vector<Integer> > g = new Vector<Vector<Integer> >();
        for (int i = 0; i < n; i++)
            g.add(new Vector<Integer> ());
        for (int i = 0; i < m; i++)
        {
            int a = sc.nextInt(), b = sc.nextInt();
            a--; b--;
            g.get(a).add(b);
            g.get(b).add(a);
        }
        int cnt = match(g, n, n);
        if (cnt < n)
            System.out.println("Impossible");
        else
            for (int i = 0; i < n; i++)
                System.out.println(par[i] + 1);
    }
}