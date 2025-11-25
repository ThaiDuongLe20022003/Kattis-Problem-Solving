using System;
using System.Collections.Generic;

public class Program
{
    private static int N;
    private static string[] words;
    private static int[,] D;
    private const int INF = 1000000000;

    private static int WordDist(int a, int b)
    {
        int res = 0;
        for (int i = 0; i < words[a].Length; ++i)
        {
            if (words[a][i] != words[b][i]) ++res;
        }
        return res;
    }

    private static string[] Diffs(int a, int b)
    {
        List<int> pos = new List<int>();
        for (int i = 0; i < words[a].Length; ++i)
        {
            if (words[a][i] != words[b][i]) pos.Add(i);
        }
        
        char[] arr1 = words[a].ToCharArray();
        char[] arr2 = words[a].ToCharArray();
        
        arr1[pos[0]] = words[b][pos[0]];
        arr2[pos[1]] = words[b][pos[1]];
        
        return new string[] { new string(arr1), new string(arr2) };
    }

    private static string Solve(List<Tuple<int, int>> pairs)
    {
        string res = "";
        foreach (var p in pairs)
        {
            int a = p.Item1, b = p.Item2;
            string[] R = Diffs(a, b);
            if (res == "") res = R[0];
            res = string.CompareOrdinal(R[0], res) < 0 ? R[0] : res;
            res = string.CompareOrdinal(R[1], res) < 0 ? R[1] : res;
        }
        return res;
    }

    private static List<Tuple<int, int>> Trace(int[,] dist, int cur)
    {
        List<Tuple<int, int>> res = new List<Tuple<int, int>>();
        Queue<int> Q = new Queue<int>();
        Q.Enqueue(cur);
        
        while (Q.Count > 0)
        {
            cur = Q.Dequeue();
            for (int i = 0; i < N; ++i)
            {
                int d = D[i, cur];
                if (d > 2) continue;
                if (d == 2 && dist[i, 0] + d == dist[cur, 1])
                {
                    res.Add(Tuple.Create(i, cur));
                }
                if (d == 1 && dist[i, 1] + d == dist[cur, 1])
                {
                    Q.Enqueue(i);
                }
            }
        }
        return res;
    }

    private static int Dijkstra(int src, int dest, out List<Tuple<int, int>> pairs)
    {
        int[,] dist = new int[N, 2];
        for (int i = 0; i < N; ++i)
        {
            dist[i, 0] = INF;
            dist[i, 1] = INF;
        }
        
        var Q = new SortedSet<Tuple<int, int, int>>(
            Comparer<Tuple<int, int, int>>.Create((a, b) => 
                a.Item1 != b.Item1 ? a.Item1.CompareTo(b.Item1) : 
                a.Item2 != b.Item2 ? a.Item2.CompareTo(b.Item2) : 
                a.Item3.CompareTo(b.Item3)));
        
        dist[src, 0] = 0;
        Q.Add(Tuple.Create(0, 0, src));
        
        while (Q.Count > 0)
        {
            var top = Q.Min;
            Q.Remove(top);
            int s = top.Item1, k = top.Item2, cur = top.Item3;
            
            for (int nxt = 0; nxt < N; ++nxt)
            {
                int d = D[cur, nxt];
                int nk = d == 2 ? 1 : 0;
                if (d > 2 || (nk == 1 && k == 1)) continue;
                if (k == 1) nk = 1;
                
                if (s + d < dist[nxt, nk])
                {
                    if (dist[nxt, nk] != INF)
                        Q.Remove(Tuple.Create(dist[nxt, nk], nk, nxt));
                    
                    dist[nxt, nk] = s + d;
                    Q.Add(Tuple.Create(s + d, nk, nxt));
                }
            }
        }
        
        pairs = new List<Tuple<int, int>>();
        if (dist[dest, 0] <= dist[dest, 1]) return dist[dest, 0];
        
        pairs = Trace(dist, dest);
        return dist[dest, 1];
    }

    public static void Main()
    {
        N = int.Parse(Console.ReadLine());
        words = new string[N];
        D = new int[N, N];
        
        for (int i = 0; i < N; ++i)
        {
            words[i] = Console.ReadLine();
            for (int j = 0; j < N; ++j) D[i, j] = INF;
        }
        
        for (int i = 0; i < N; ++i)
        {
            for (int j = i + 1; j < N; ++j)
            {
                D[i, j] = D[j, i] = WordDist(i, j);
            }
        }
        
        List<Tuple<int, int>> pairs;
        int steps = Dijkstra(0, 1, out pairs);
        
        if (steps == INF || pairs.Count == 0)
        {
            Console.WriteLine("0");
        }
        else
        {
            Console.WriteLine(Solve(pairs));
        }
        Console.WriteLine(steps == INF ? -1 : steps);
    }
}