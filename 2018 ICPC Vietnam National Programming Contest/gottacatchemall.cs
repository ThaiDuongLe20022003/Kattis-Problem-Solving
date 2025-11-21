using System;
using System.Collections.Generic;
using System.Linq;

class Program {
    static void Main() {
        int n = int.Parse(Console.ReadLine());
        
        List<(int, int)> junctions = new List<(int, int)>();
        for (int i = 0; i < n - 1; i++) {
            int[] edge = Console.ReadLine().Split().Select(int.Parse).ToArray();
            int u = edge[0], v = edge[1];
            if (u > v) (u, v) = (v, u);
            junctions.Add((u, v));
        }
        
        junctions = junctions.Distinct().OrderBy(x => x.Item1).ThenBy(x => x.Item2).ToList();
        
        int[] count = new int[n + 1];
        foreach (var (u, v) in junctions) {
            count[u]++;
            count[v]++;
        }
        
        List<int>[] connected = new List<int>[n + 1];
        for (int i = 1; i <= n; i++) {
            connected[i] = new List<int>();
        }
        
        foreach (var (u, v) in junctions) {
            if (count[u] != count[v] ? count[u] > count[v] : u < v) {
                connected[u].Add(v);
            } else {
                connected[v].Add(u);
            }
        }
        
        int[] visited = new int[n + 1];
        long total = 0, optimal = 0;
        
        for (int i = 1; i <= n; i++) {
            if (count[i] > 0) {
                total += (long)count[i] * (count[i] - 1);
            }
            foreach (int j in connected[i]) {
                visited[j] = i;
            }
            foreach (int j in connected[i]) {
                foreach (int k in connected[j]) {
                    if (visited[k] == i) {
                        optimal++;
                    }
                }
            }
        }
        
        Console.WriteLine(total - 6 * optimal);
    }
}