using System;
using System.Collections.Generic;
using System.Linq;

public class Program
{
    const double INF = double.MaxValue;
    
    class Edge
    {
        public int To { get; set; }
        public double Cost { get; set; }
    }
    
    public static void Main()
    {
        string line;
        while ((line = Console.ReadLine()) != null)
        {
            int n = int.Parse(line);
            if (n == 0) break;
            
            var stones = new Tuple<int, int, int>[n];
            var uniqueWidthsSet = new HashSet<int>();
            
            for (int i = 0; i < n; i++)
            {
                var parts = Console.ReadLine().Split();
                int a = int.Parse(parts[0]);
                int b = int.Parse(parts[1]);
                int h = int.Parse(parts[2]);
                stones[i] = Tuple.Create(a, b, h);
                uniqueWidthsSet.Add(a);
                uniqueWidthsSet.Add(b);
            }
            
            var endpoints = Console.ReadLine().Split();
            int startWidth = int.Parse(endpoints[0]);
            int endWidth = int.Parse(endpoints[1]);
            uniqueWidthsSet.Add(startWidth);
            uniqueWidthsSet.Add(endWidth);
            
            // Map widths to node IDs
            var widthToId = new Dictionary<int, int>();
            var idToWidth = new List<int>();
            int currentId = 0;
            foreach (int width in uniqueWidthsSet.OrderBy(x => x))
            {
                widthToId[width] = currentId;
                idToWidth.Add(width);
                currentId++;
            }
            int numNodes = currentId;
            
            // Build graph
            var adj = new List<Edge>[numNodes];
            for (int i = 0; i < numNodes; i++)
            {
                adj[i] = new List<Edge>();
            }
            
            foreach (var stone in stones)
            {
                int a = stone.Item1, b = stone.Item2, h = stone.Item3;
                double cost = (a + b) * h;
                int u = widthToId[a];
                int v = widthToId[b];
                adj[u].Add(new Edge { To = v, Cost = cost });
                adj[v].Add(new Edge { To = u, Cost = cost });
            }
            
            // Dijkstra's algorithm
            int startNode = widthToId[startWidth];
            int endNode = widthToId[endWidth];
            double[] dist = new double[numNodes];
            for (int i = 0; i < numNodes; i++)
            {
                dist[i] = INF;
            }
            
            var pq = new SortedSet<Tuple<double, int>>(
                Comparer<Tuple<double, int>>.Create((a, b) => 
                {
                    int cmp = a.Item1.CompareTo(b.Item1);
                    return cmp != 0 ? cmp : a.Item2.CompareTo(b.Item2);
                }));
            
            dist[startNode] = 0;
            pq.Add(Tuple.Create(0.0, startNode));
            
            while (pq.Count > 0)
            {
                var current = pq.Min;
                pq.Remove(current);
                double d = current.Item1;
                int u = current.Item2;
                
                if (d > dist[u]) continue;
                if (u == endNode) break;
                
                foreach (var edge in adj[u])
                {
                    int v = edge.To;
                    double weight = edge.Cost;
                    if (dist[u] + weight < dist[v])
                    {
                        dist[v] = dist[u] + weight;
                        pq.Add(Tuple.Create(dist[v], v));
                    }
                }
            }
            
            double minCostDollars = dist[endNode] / 100.0;
            Console.WriteLine($"{minCostDollars:F2}");
        }
    }
}