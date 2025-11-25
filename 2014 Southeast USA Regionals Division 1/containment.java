import java.util.*;
import java.io.*;

public class containment {
    static class Arc {
        int u, rev;
        int cap, initial_cap;
        
        Arc(int u, int rev, int cap) {
            this.u = u;
            this.rev = rev;
            this.cap = cap;
            this.initial_cap = cap;
        }
    }
    
    static class FlowNetwork {
        int n;
        List<Arc>[] network;
        int[] dist;
        int[] iter;
        
        @SuppressWarnings("unchecked")
        FlowNetwork(int n) {
            this.n = n;
            network = new ArrayList[n];
            dist = new int[n];
            iter = new int[n];
            
            for (int i = 0; i < n; i++) {
                network[i] = new ArrayList<>();
            }
        }
        
        void addArc(int u, int v, int cap_uv, int cap_vu) {
            if (u == v) return;
            
            network[u].add(new Arc(v, network[v].size(), cap_uv));
            network[v].add(new Arc(u, network[u].size() - 1, cap_vu));
        }
        
        void addArc(int u, int v, int cap_uv) {
            addArc(u, v, cap_uv, 0);
        }
        
        boolean bfs(int s, int t) {
            Arrays.fill(dist, -1);
            dist[s] = 0;
            
            Queue<Integer> q = new LinkedList<>();
            q.add(s);
            
            while (!q.isEmpty()) {
                int v = q.poll();
                for (Arc arc : network[v]) {
                    if (arc.cap > 0 && dist[arc.u] == -1) {
                        dist[arc.u] = dist[v] + 1;
                        q.add(arc.u);
                    }
                }
            }
            return dist[t] != -1;
        }
        
        int dfs(int v, int t, int flow) {
            if (v == t) return flow;
            
            for (; iter[v] < network[v].size(); iter[v]++) {
                Arc arc = network[v].get(iter[v]);
                if (arc.cap > 0 && dist[arc.u] == dist[v] + 1) {
                    int f = dfs(arc.u, t, Math.min(flow, arc.cap));
                    if (f > 0) {
                        arc.cap -= f;
                        network[arc.u].get(arc.rev).cap += f;
                        return f;
                    }
                }
            }
            return 0;
        }
        
        int maxFlow(int s, int t) {
            int flow = 0;
            
            while (bfs(s, t)) {
                Arrays.fill(iter, 0);
                int f;
                while ((f = dfs(s, t, Integer.MAX_VALUE)) > 0) {
                    flow += f;
                }
            }
            return flow;
        }
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        
        FlowNetwork fn = new FlowNetwork(1002);
        int s = 1000, t = 1001;
        
        // Build the 3D grid network
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    int u = i * 100 + j * 10 + k;
                    fn.addArc(u, i > 0 ? (i - 1) * 100 + j * 10 + k : t, 1);
                    fn.addArc(u, i < 9 ? (i + 1) * 100 + j * 10 + k : t, 1);
                    fn.addArc(u, j > 0 ? i * 100 + (j - 1) * 10 + k : t, 1);
                    fn.addArc(u, j < 9 ? i * 100 + (j + 1) * 10 + k : t, 1);
                    fn.addArc(u, k > 0 ? i * 100 + j * 10 + (k - 1) : t, 1);
                    fn.addArc(u, k < 9 ? i * 100 + j * 10 + (k + 1) : t, 1);
                }
            }
        }
        
        // Add source connections
        for (int i = 0; i < n; i++) {
            String[] inputs = br.readLine().split(" ");
            int x = Integer.parseInt(inputs[0]);
            int y = Integer.parseInt(inputs[1]);
            int z = Integer.parseInt(inputs[2]);
            fn.addArc(s, x * 100 + y * 10 + z, 6);
        }
        
        int result = fn.maxFlow(s, t);
        System.out.println(result);
    }
}