import java.io.*;
import java.util.*;

public class mountainouslandscape
{
    long[] x, y;

    long det(int i, int j, int k)
    {
        return (x[j]-x[i])*(y[k]-y[i]) - (x[k]-x[i])*(y[j]-y[i]);
    }

    class Node
    {
        int[]   hull;
        int     next;

        long best(int q)
        {
            if (hull.length == 0)
                return -1;
            while (next+1 < hull.length && det(q, q+1, hull[next+1]) > det(q, q+1, hull[next]))
                next++;
            return det(q, q+1, hull[next]);
        }
    }

    Node[] tree;

    mountainouslandscape(BufferedReader rd, PrintWriter wr) throws IOException
    {
        final int n = Integer.parseInt(rd.readLine());
        x = new long[n];
        y = new long[n];
        for (int i=0; i<n; i++)
        {
            String[] ss = rd.readLine().split(" ");
            x[i] = Long.parseLong(ss[0]);
            y[i] = Long.parseLong(ss[1]);
        }
        int nn = 1;
        while (nn < n)
            nn *= 2;
        tree = new Node[2*nn];
        for (int i=0; i<n; i++)
        {
            tree[nn+i] = new Node();
            tree[nn+i].hull = new int[] { i };
        }
        for (int i=n; i<nn; i++)
        {
            tree[nn+i] = new Node();
            tree[nn+i].hull = new int[0];
        }
        for (int i=nn-1; i>0; i--)
        {
            int t = tree[2*i].hull.length;
            int[] h = Arrays.copyOf(tree[2*i].hull, t + tree[2*i+1].hull.length);
            for (int j : tree[2*i+1].hull)
            {
                while (t>1 && det(h[t-2], h[t-1], j) >= 0)
                    t--;
                h[t++] = j;
            }
            tree[i] = new Node();
            tree[i].hull = Arrays.copyOf(h, t);
        }
        int[] results = new int[n-2];
        ArrayList<Integer> queries = new ArrayList<Integer>();
        for (int i=0; i<n-2; i++)
            queries.add(i);
        Collections.sort(queries, new Comparator<Integer>()
        {
            public int compare(Integer p, Integer q)
            {
                long d = (x[p+1]-x[p])*(y[q+1]-y[q]) - (x[q+1]-x[q])*(y[p+1]-y[p]);
                return (d < 0) ? -1 : (d == 0) ? 0 : +1;
            }
        });
        for (int q : queries)
        {
            int t = nn+q+1;
            while (t > 0)
            {
                if (t % 2 == 0 && tree[t+1].best(q) > 0)
                {
                    t++;
                    while (t < nn)
                    {
                        if (tree[2*t].best(q) > 0)
                            t = 2*t;
                        else
                            t = 2*t+1;
                    }
                    results[q] = t-nn;
                    break;
                }
                t /= 2;
            }
        }
        for (int r : results)
        {
            wr.print(r);
            wr.print(" ");
        }
        wr.println("0");
    }

    public static void main(String[] args) throws IOException 
    {
        BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter wr = new PrintWriter(System.out);
        int T = Integer.parseInt(rd.readLine());
        for (int t=0; t<T; t++)
            new mountainouslandscape(rd, wr);
        wr.close();
    }
}