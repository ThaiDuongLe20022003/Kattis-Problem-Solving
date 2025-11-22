import java.util.*;
import java.io.*;

public class walkway {
    static final double INF = Double.MAX_VALUE;
    
    static class Edge {
        int to;
        double cost;
        Edge(int to, double cost) {
            this.to = to;
            this.cost = cost;
        }
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        
        while ((line = br.readLine()) != null) {
            int n = Integer.parseInt(line);
            if (n == 0) break;
            
            int[][] stones = new int[n][3];
            Set<Integer> uniqueWidthsSet = new TreeSet<>();
            
            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                stones[i][0] = Integer.parseInt(st.nextToken());
                stones[i][1] = Integer.parseInt(st.nextToken());
                stones[i][2] = Integer.parseInt(st.nextToken());
                uniqueWidthsSet.add(stones[i][0]);
                uniqueWidthsSet.add(stones[i][1]);
            }
            
            StringTokenizer st = new StringTokenizer(br.readLine());
            int startWidth = Integer.parseInt(st.nextToken());
            int endWidth = Integer.parseInt(st.nextToken());
            uniqueWidthsSet.add(startWidth);
            uniqueWidthsSet.add(endWidth);
            
            // Map widths to node IDs
            Map<Integer, Integer> widthToId = new HashMap<>();
            List<Integer> idToWidth = new ArrayList<>();
            int currentId = 0;
            for (int width : uniqueWidthsSet) {
                widthToId.put(width, currentId);
                idToWidth.add(width);
                currentId++;
            }
            int numNodes = currentId;
            
            // Build graph
            List<List<Edge>> adj = new ArrayList<>();
            for (int i = 0; i < numNodes; i++) {
                adj.add(new ArrayList<>());
            }
            
            for (int i = 0; i < n; i++) {
                int a = stones[i][0], b = stones[i][1], h = stones[i][2];
                double cost = (a + b) * h;
                int u = widthToId.get(a);
                int v = widthToId.get(b);
                adj.get(u).add(new Edge(v, cost));
                adj.get(v).add(new Edge(u, cost));
            }
            
            // Dijkstra's algorithm
            int startNode = widthToId.get(startWidth);
            int endNode = widthToId.get(endWidth);
            double[] dist = new double[numNodes];
            Arrays.fill(dist, INF);
            
            PriorityQueue<double[]> pq = new PriorityQueue<>(
                (a, b) -> Double.compare(a[0], b[0])
            );
            
            dist[startNode] = 0;
            pq.offer(new double[]{0.0, startNode});
            
            while (!pq.isEmpty()) {
                double[] current = pq.poll();
                double d = current[0];
                int u = (int) current[1];
                
                if (d > dist[u]) continue;
                if (u == endNode) break;
                
                for (Edge edge : adj.get(u)) {
                    int v = edge.to;
                    double weight = edge.cost;
                    if (dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                        pq.offer(new double[]{dist[v], v});
                    }
                }
            }
            
            double minCostDollars = dist[endNode] / 100.0;
            System.out.printf("%.2f\n", minCostDollars);
        }
    }
}