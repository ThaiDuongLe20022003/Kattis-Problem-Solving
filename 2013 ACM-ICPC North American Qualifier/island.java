import java.util.*;
import java.io.*;

public class island {
    static int R, C;
    static char[][] grid;
    static boolean[][] visitedIsland;
    static boolean[][] visitedBridge;
    static int[][] islandIdGrid;
    static int[] dr = {-1, 1, 0, 0};
    static int[] dc = {0, 0, -1, 1};
    
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
        
        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
            }
        }
    }
    
    static boolean isValid(int r, int c) {
        return r >= 0 && r < R && c >= 0 && c < C;
    }
    
    static void bfsIsland(int r, int c, int id) {
        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{r, c});
        visitedIsland[r][c] = true;
        islandIdGrid[r][c] = id;
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int currR = curr[0], currC = curr[1];
            
            for (int i = 0; i < 4; i++) {
                int nr = currR + dr[i];
                int nc = currC + dc[i];
                
                if (isValid(nr, nc) && !visitedIsland[nr][nc] && 
                    (grid[nr][nc] == '#' || grid[nr][nc] == 'X')) {
                    visitedIsland[nr][nc] = true;
                    islandIdGrid[nr][nc] = id;
                    queue.offer(new int[]{nr, nc});
                }
            }
        }
    }
    
    static Set<Integer> bfsFindIslandsForBridge(int r, int c) {
        Set<Integer> adjacentIslandIds = new HashSet<>();
        Queue<int[]> queue = new LinkedList<>();
        
        queue.offer(new int[]{r, c});
        visitedBridge[r][c] = true;
        
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int currR = curr[0], currC = curr[1];
            
            for (int i = 0; i < 4; i++) {
                int nr = currR + dr[i];
                int nc = currC + dc[i];
                
                if (isValid(nr, nc)) {
                    if (grid[nr][nc] == 'B' && !visitedBridge[nr][nc]) {
                        visitedBridge[nr][nc] = true;
                        queue.offer(new int[]{nr, nc});
                    } else if (grid[nr][nc] == 'X') {
                        int islandId = islandIdGrid[nr][nc];
                        if (islandId != 0) {
                            adjacentIslandIds.add(islandId);
                        }
                    }
                }
            }
        }
        return adjacentIslandIds;
    }
    
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        int mapNum = 1;
        boolean firstMapOutput = true;
        
        while ((line = br.readLine()) != null) {
            while (line != null && line.isEmpty() && br.ready()) {
                line = br.readLine();
            }
            if (line == null) break;
            
            if (!firstMapOutput) {
                System.out.println();
            }
            firstMapOutput = false;
            
            List<String> gridLines = new ArrayList<>();
            gridLines.add(line);
            
            while ((line = br.readLine()) != null && !line.isEmpty()) {
                gridLines.add(line);
            }
            
            R = gridLines.size();
            C = gridLines.get(0).length();
            
            grid = new char[R][C];
            visitedIsland = new boolean[R][C];
            visitedBridge = new boolean[R][C];
            islandIdGrid = new int[R][C];
            
            for (int i = 0; i < R; i++) {
                grid[i] = gridLines.get(i).toCharArray();
            }
            
            // 1. Identify Islands
            int islandCount = 0;
            for (int r = 0; r < R; r++) {
                for (int c = 0; c < C; c++) {
                    if (!visitedIsland[r][c] && (grid[r][c] == '#' || grid[r][c] == 'X')) {
                        islandCount++;
                        bfsIsland(r, c, islandCount);
                    }
                }
            }
            
            // 2. Count Bridges & Connect Islands
            DSU dsu = new DSU(islandCount);
            int bridgeCount = 0;
            int busCount = islandCount;
            
            for (int r = 0; r < R; r++) {
                for (int c = 0; c < C; c++) {
                    if (grid[r][c] == 'B' && !visitedBridge[r][c]) {
                        bridgeCount++;
                        Set<Integer> connectedIslands = bfsFindIslandsForBridge(r, c);
                        
                        if (connectedIslands.size() == 2) {
                            Iterator<Integer> it = connectedIslands.iterator();
                            int id1 = it.next();
                            int id2 = it.next();
                            
                            if (dsu.find(id1) != dsu.find(id2)) {
                                dsu.unite(id1, id2);
                                busCount--;
                            }
                        }
                    }
                }
            }
            
            System.out.println("Map " + mapNum++);
            System.out.println("islands: " + islandCount);
            System.out.println("bridges: " + bridgeCount);
            System.out.println("buses needed: " + busCount);
        }
    }
}