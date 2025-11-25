import java.util.*;
import java.io.*;

public class wordladder2 {
    static int N, INF = 1000000000;
    static String[] words;
    static int[][] D;
    
    static int wordDist(int a, int b) {
        int res = 0;
        for (int i = 0; i < words[a].length(); ++i) {
            if (words[a].charAt(i) != words[b].charAt(i)) ++res;
        }
        return res;
    }
    
    static String[] diffs(int a, int b) {
        List<Integer> pos = new ArrayList<>();
        for (int i = 0; i < words[a].length(); ++i) {
            if (words[a].charAt(i) != words[b].charAt(i)) pos.add(i);
        }
        
        char[] arr1 = words[a].toCharArray();
        char[] arr2 = words[a].toCharArray();
        
        arr1[pos.get(0)] = words[b].charAt(pos.get(0));
        arr2[pos.get(1)] = words[b].charAt(pos.get(1));
        
        return new String[]{new String(arr1), new String(arr2)};
    }
    
    static String solve(List<int[]> pairs) {
        String res = "";
        for (int[] p : pairs) {
            int a = p[0], b = p[1];
            String[] R = diffs(a, b);
            if (res.isEmpty()) res = R[0];
            if (R[0].compareTo(res) < 0) res = R[0];
            if (R[1].compareTo(res) < 0) res = R[1];
        }
        return res;
    }
    
    static List<int[]> trace(int[][] dist, int cur) {
        List<int[]> res = new ArrayList<>();
        Queue<Integer> Q = new LinkedList<>();
        Q.add(cur);
        
        while (!Q.isEmpty()) {
            cur = Q.poll();
            for (int i = 0; i < N; ++i) {
                int d = D[i][cur];
                if (d > 2) continue;
                if (d == 2 && dist[i][0] + d == dist[cur][1]) {
                    res.add(new int[]{i, cur});
                }
                if (d == 1 && dist[i][1] + d == dist[cur][1]) {
                    Q.add(i);
                }
            }
        }
        return res;
    }
    
    static int dijkstra(int src, int dest, List<int[]> pairs) {
        int[][] dist = new int[N][2];
        for (int i = 0; i < N; ++i) {
            Arrays.fill(dist[i], INF);
        }
        
        PriorityQueue<int[]> Q = new PriorityQueue<>((a, b) -> 
            a[0] != b[0] ? Integer.compare(a[0], b[0]) : 
            a[1] != b[1] ? Integer.compare(a[1], b[1]) : 
            Integer.compare(a[2], b[2]));
        
        dist[src][0] = 0;
        Q.add(new int[]{0, 0, src});
        
        while (!Q.isEmpty()) {
            int[] top = Q.poll();
            int s = top[0], k = top[1], cur = top[2];
            
            for (int nxt = 0; nxt < N; ++nxt) {
                int d = D[cur][nxt];
                int nk = d == 2 ? 1 : 0;
                if (d > 2 || (nk == 1 && k == 1)) continue;
                if (k == 1) nk = 1;
                
                if (s + d < dist[nxt][nk]) {
                    dist[nxt][nk] = s + d;
                    Q.add(new int[]{s + d, nk, nxt});
                }
            }
        }
        
        if (dist[dest][0] <= dist[dest][1]) return dist[dest][0];
        
        pairs.addAll(trace(dist, dest));
        return dist[dest][1];
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        N = Integer.parseInt(br.readLine());
        words = new String[N];
        D = new int[N][N];
        
        for (int i = 0; i < N; ++i) {
            words[i] = br.readLine();
            Arrays.fill(D[i], INF);
        }
        
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                D[i][j] = D[j][i] = wordDist(i, j);
            }
        }
        
        List<int[]> pairs = new ArrayList<>();
        int steps = dijkstra(0, 1, pairs);
        
        if (steps == INF || pairs.isEmpty()) {
            System.out.println("0");
        } else {
            System.out.println(solve(pairs));
        }
        System.out.println(steps == INF ? -1 : steps);
    }
}