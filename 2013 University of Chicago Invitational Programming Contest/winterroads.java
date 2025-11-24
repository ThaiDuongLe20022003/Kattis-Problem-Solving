import java.util.*;
import java.io.*;

public class winterroads {
    static class Edge {
        int u, v, id;
        long cap;
        Edge(int u, int v, int id, long cap) {
            this.u = u;
            this.v = v;
            this.id = id;
            this.cap = cap;
        }
    }
    
    static class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n + 1];
            for (int i = 0; i <= n; i++) {
                parent[i] = i;
            }
        }
        int find(int i) {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        }
        boolean unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
                return true;
            }
            return false;
        }
    }
    
    static List<int[]>[] adj; // [neighbor, road_id]
    static Edge[] allEdges;
    static long[] capacities;
    static int n, m, e;
    
    static boolean checkPath(int a, int b, long w) {
        boolean[] visited = new boolean[n + 1];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(a);
        visited[a] = true;
        
        while (!queue.isEmpty()) {
            int u = queue.poll();
            if (u == b) return true;
            
            for (int[] edge : adj[u]) {
                int v = edge[0];
                int rId = edge[1];
                if (!visited[v] && capacities[rId] >= w) {
                    visited[v] = true;
                    queue.offer(v);
                }
            }
        }
        return false;
    }
    
    static void removeFromAdj(int u, int v, int rId) {
        adj[u].removeIf(edge -> edge[0] == v && edge[1] == rId);
        adj[v].removeIf(edge -> edge[0] == u && edge[1] == rId);
    }
    
    static long[] findPathBottleneck(int start, int end) {
        boolean[] visited = new boolean[n + 1];
        int[] parent = new int[n + 1];
        int[] roadToParent = new int[n + 1];
        Queue<Integer> queue = new LinkedList<>();
        queue.offer(start);
        visited[start] = true;
        boolean found = false;
        
        while (!queue.isEmpty() && !found) {
            int u = queue.poll();
            
            for (int[] edge : adj[u]) {
                int v = edge[0];
                int rId = edge[1];
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    roadToParent[v] = rId;
                    queue.offer(v);
                    if (v == end) {
                        found = true;
                        break;
                    }
                }
            }
        }
        
        if (!found) return new long[]{-1, -1};
        
        long minCap = Long.MAX_VALUE;
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
        
        return new long[]{minCap, minRoadId};
    }
    
    static void addEdge(int u, int v, int rId) {
        adj[u].add(new int[]{v, rId});
        adj[v].add(new int[]{u, rId});
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        
        adj = new ArrayList[n + 1];
        for (int i = 0; i <= n; i++) adj[i] = new ArrayList<>();
        allEdges = new Edge[m + 1];
        capacities = new long[m + 1];
        
        List<Edge> initialEdges = new ArrayList<>();
        for (int i = 1; i <= m; i++) {
            st = new StringTokenizer(br.readLine());
            int u = Integer.parseInt(st.nextToken());
            int v = Integer.parseInt(st.nextToken());
            long cap = Long.parseLong(st.nextToken());
            allEdges[i] = new Edge(u, v, i, cap);
            capacities[i] = cap;
            initialEdges.add(allEdges[i]);
        }
        
        // Build initial MSF
        initialEdges.sort((a, b) -> Long.compare(b.cap, a.cap));
        DSU dsu = new DSU(n);
        
        for (Edge edge : initialEdges) {
            if (dsu.unite(edge.u, edge.v)) {
                addEdge(edge.u, edge.v, edge.id);
            }
        }
        
        e = Integer.parseInt(br.readLine());
        for (int i = 0; i < e; i++) {
            st = new StringTokenizer(br.readLine());
            char type = st.nextToken().charAt(0);
            
            if (type == 'S') {
                int a = Integer.parseInt(st.nextToken());
                int b = Integer.parseInt(st.nextToken());
                long w = Long.parseLong(st.nextToken());
                System.out.println(checkPath(a, b, w) ? 1 : 0);
            } else {
                int rId = Integer.parseInt(st.nextToken());
                long cNew = Long.parseLong(st.nextToken());
                long cOld = capacities[rId];
                capacities[rId] = cNew;
                int u = allEdges[rId].u;
                int v = allEdges[rId].v;
                
                boolean wasInMsf = adj[u].stream()
                    .anyMatch(edge -> edge[0] == v && edge[1] == rId);
                
                if (wasInMsf && cNew < cOld) {
                    removeFromAdj(u, v, rId);
                    
                    // Find component containing u
                    boolean[] inTU = new boolean[n + 1];
                    Queue<Integer> compQueue = new LinkedList<>();
                    compQueue.offer(u);
                    inTU[u] = true;
                    
                    while (!compQueue.isEmpty()) {
                        int curr = compQueue.poll();
                        for (int[] edge : adj[curr]) {
                            int neighbor = edge[0];
                            if (!inTU[neighbor]) {
                                inTU[neighbor] = true;
                                compQueue.offer(neighbor);
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
                        addEdge(allEdges[bestRId].u, allEdges[bestRId].v, bestRId);
                    }
                } else if (!wasInMsf && cNew > cOld) {
                    long[] result = findPathBottleneck(u, v);
                    long minCap = result[0];
                    int minRoadId = (int) result[1];
                    if (minCap != -1 && cNew > minCap) {
                        removeFromAdj(allEdges[minRoadId].u, allEdges[minRoadId].v, minRoadId);
                        addEdge(u, v, rId);
                    }
                }
            }
        }
    }
}