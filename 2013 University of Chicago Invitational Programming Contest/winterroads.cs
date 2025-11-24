using System;
using System.Collections.Generic;
using System.Linq;

public class Edge {
    public int u, v, id;
    public long cap;
}

public class DSU {
    private int[] parent;
    
    public DSU(int n) {
        parent = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    public int Find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = Find(parent[i]);
    }
    
    public bool Unite(int i, int j) {
        int root_i = Find(i);
        int root_j = Find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
}

public class Program {
    static List<(int, int)>[] adj;
    static Edge[] allEdges;
    static long[] capacities;
    static int n, m, e;
    
    static bool CheckPath(int a, int b, long w) {
        bool[] visited = new bool[n + 1];
        Queue<int> queue = new Queue<int>();
        queue.Enqueue(a);
        visited[a] = true;
        
        while (queue.Count > 0) {
            int u = queue.Dequeue();
            if (u == b) return true;
            
            foreach (var (v, rId) in adj[u]) {
                if (!visited[v] && capacities[rId] >= w) {
                    visited[v] = true;
                    queue.Enqueue(v);
                }
            }
        }
        return false;
    }
    
    static void RemoveFromAdj(int u, int v, int rId) {
        adj[u].RemoveAll(x => x.Item1 == v && x.Item2 == rId);
        adj[v].RemoveAll(x => x.Item1 == u && x.Item2 == rId);
    }
    
    static (long, int) FindPathBottleneck(int start, int end) {
        bool[] visited = new bool[n + 1];
        int[] parent = new int[n + 1];
        int[] roadToParent = new int[n + 1];
        Queue<int> queue = new Queue<int>();
        
        queue.Enqueue(start);
        visited[start] = true;
        bool found = false;
        
        while (queue.Count > 0 && !found) {
            int u = queue.Dequeue();
            
            foreach (var (v, rId) in adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    roadToParent[v] = rId;
                    queue.Enqueue(v);
                    if (v == end) {
                        found = true;
                        break;
                    }
                }
            }
        }
        
        if (!found) return (-1, -1);
        
        long minCap = long.MaxValue;
        int minRoadId = -1;
        int curr = end;
        
        while (curr != start) {
            int rId = roadToParent[curr];
            if (capacities[rId] < minCap) {
                minCap = capacities[rId];
                minRoadId = rId;
            }
            curr = parent[curr];
        }
        
        return (minCap, minRoadId);
    }
    
    static void AddEdge(int u, int v, int rId) {
        adj[u].Add((v, rId));
        adj[v].Add((u, rId));
    }
    
    public static void Main() {
        string[] input = Console.ReadLine().Split();
        n = int.Parse(input[0]);
        m = int.Parse(input[1]);
        
        adj = new List<(int, int)>[n + 1];
        for (int i = 0; i <= n; i++) adj[i] = new List<(int, int)>();
        allEdges = new Edge[m + 1];
        capacities = new long[m + 1];
        
        List<Edge> initialEdges = new List<Edge>();
        for (int i = 1; i <= m; i++) {
            input = Console.ReadLine().Split();
            allEdges[i] = new Edge {
                id = i,
                u = int.Parse(input[0]),
                v = int.Parse(input[1]),
                cap = long.Parse(input[2])
            };
            capacities[i] = allEdges[i].cap;
            initialEdges.Add(allEdges[i]);
        }
        
        // Build initial MSF
        initialEdges = initialEdges.OrderByDescending(e => e.cap).ToList();
        DSU dsu = new DSU(n);
        
        foreach (var edge in initialEdges) {
            if (dsu.Unite(edge.u, edge.v)) {
                AddEdge(edge.u, edge.v, edge.id);
            }
        }
        
        e = int.Parse(Console.ReadLine());
        for (int i = 0; i < e; i++) {
            input = Console.ReadLine().Split();
            char type = input[0][0];
            
            if (type == 'S') {
                int a = int.Parse(input[1]);
                int b = int.Parse(input[2]);
                long w = long.Parse(input[3]);
                Console.WriteLine(CheckPath(a, b, w) ? "1" : "0");
            } else {
                int rId = int.Parse(input[1]);
                long cNew = long.Parse(input[2]);
                long cOld = capacities[rId];
                capacities[rId] = cNew;
                int u = allEdges[rId].u;
                int v = allEdges[rId].v;
                
                bool wasInMsf = adj[u].Any(x => x.Item1 == v && x.Item2 == rId);
                
                if (wasInMsf && cNew < cOld) {
                    RemoveFromAdj(u, v, rId);
                    
                    // Find component containing u
                    bool[] inTU = new bool[n + 1];
                    Queue<int> queue = new Queue<int>();
                    queue.Enqueue(u);
                    inTU[u] = true;
                    
                    while (queue.Count > 0) {
                        int curr = queue.Dequeue();
                        foreach (var (neighbor, _) in adj[curr]) {
                            if (!inTU[neighbor]) {
                                inTU[neighbor] = true;
                                queue.Enqueue(neighbor);
                            }
                        }
                    }
                    
                    // Find best replacement edge
                    long maxCap = -1;
                    int bestRId = -1;
                    for (int j = 1; j <= m; j++) {
                        if (inTU[allEdges[j].u] != inTU[allEdges[j].v]) {
                            if (capacities[j] > maxCap) {
                                maxCap = capacities[j];
                                bestRId = j;
                            }
                        }
                    }
                    
                    if (bestRId != -1) {
                        AddEdge(allEdges[bestRId].u, allEdges[bestRId].v, bestRId);
                    }
                } else if (!wasInMsf && cNew > cOld) {
                    var (minCap, minRoadId) = FindPathBottleneck(u, v);
                    if (minCap != -1 && cNew > minCap) {
                        RemoveFromAdj(allEdges[minRoadId].u, allEdges[minRoadId].v, minRoadId);
                        AddEdge(u, v, rId);
                    }
                }
            }
        }
    }
}