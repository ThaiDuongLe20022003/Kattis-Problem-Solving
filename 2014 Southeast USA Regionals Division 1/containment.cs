using System;
using System.Collections.Generic;

public class FlowNetwork {
    public class Arc {
        public int u, rev;
        public int cap, initial_cap;
        
        public Arc(int u, int rev, int cap) {
            this.u = u;
            this.rev = rev;
            this.cap = cap;
            this.initial_cap = cap;
        }
    }
    
    public int n;
    public List<Arc>[] network;
    public int[] dist;
    public int[] iter;
    
    public FlowNetwork(int n) {
        this.n = n;
        network = new List<Arc>[n];
        dist = new int[n];
        iter = new int[n];
        
        for (int i = 0; i < n; i++) {
            network[i] = new List<Arc>();
        }
    }
    
    public void AddArc(int u, int v, int cap_uv, int cap_vu = 0) {
        if (u == v) return;
        
        network[u].Add(new Arc(v, network[v].Count, cap_uv));
        network[v].Add(new Arc(u, network[u].Count - 1, cap_vu));
    }
    
    public bool Bfs(int s, int t) {
        Array.Fill(dist, -1);
        dist[s] = 0;
        
        Queue<int> q = new Queue<int>();
        q.Enqueue(s);
        
        while (q.Count > 0) {
            int v = q.Dequeue();
            foreach (var arc in network[v]) {
                if (arc.cap > 0 && dist[arc.u] == -1) {
                    dist[arc.u] = dist[v] + 1;
                    q.Enqueue(arc.u);
                }
            }
        }
        return dist[t] != -1;
    }
    
    public int Dfs(int v, int t, int flow) {
        if (v == t) return flow;
        
        for (; iter[v] < network[v].Count; iter[v]++) {
            var arc = network[v][iter[v]];
            if (arc.cap > 0 && dist[arc.u] == dist[v] + 1) {
                int f = Dfs(arc.u, t, Math.Min(flow, arc.cap));
                if (f > 0) {
                    arc.cap -= f;
                    network[arc.u][arc.rev].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }
    
    public int MaxFlow(int s, int t) {
        int flow = 0;
        
        while (Bfs(s, t)) {
            Array.Fill(iter, 0);
            int f;
            while ((f = Dfs(s, t, int.MaxValue)) > 0) {
                flow += f;
            }
        }
        return flow;
    }
}

public class Program {
    public static void Main() {
        int n = int.Parse(Console.ReadLine());
        
        FlowNetwork fn = new FlowNetwork(1002);
        int s = 1000, t = 1001;
        
        // Build the 3D grid network
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    int u = i * 100 + j * 10 + k;
                    fn.AddArc(u, i > 0 ? (i - 1) * 100 + j * 10 + k : t, 1);
                    fn.AddArc(u, i < 9 ? (i + 1) * 100 + j * 10 + k : t, 1);
                    fn.AddArc(u, j > 0 ? i * 100 + (j - 1) * 10 + k : t, 1);
                    fn.AddArc(u, j < 9 ? i * 100 + (j + 1) * 10 + k : t, 1);
                    fn.AddArc(u, k > 0 ? i * 100 + j * 10 + (k - 1) : t, 1);
                    fn.AddArc(u, k < 9 ? i * 100 + j * 10 + (k + 1) : t, 1);
                }
            }
        }
        
        // Add source connections
        for (int i = 0; i < n; i++) {
            string[] inputs = Console.ReadLine().Split();
            int x = int.Parse(inputs[0]);
            int y = int.Parse(inputs[1]);
            int z = int.Parse(inputs[2]);
            fn.AddArc(s, x * 100 + y * 10 + z, 6);
        }
        
        int result = fn.MaxFlow(s, t);
        Console.WriteLine(result);
    }
}

// Extension method for Array.Fill for older .NET versions
public static class ArrayExtensions {
    public static void Fill<T>(this T[] array, T value) {
        for (int i = 0; i < array.Length; i++) {
            array[i] = value;
        }
    }
}