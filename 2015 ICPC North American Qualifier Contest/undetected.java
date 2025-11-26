import java.util.*;

class UnionFind {
    private int[] p, rank, setSize;
    public int numSets;
    
    public UnionFind(int n) {
        numSets = n;
        setSize = new int[n];
        rank = new int[n];
        p = new int[n];
        for (int i = 0; i < n; i++) {
            p[i] = i;
            setSize[i] = 1;
        }
    }
    
    public int findSet(int i) {
        return (p[i] == i) ? i : (p[i] = findSet(p[i]));
    }
    
    public boolean isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
    
    public void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            numSets--;
            int x = findSet(i);
            int y = findSet(j);
            
            if (rank[x] > rank[y]) {
                p[y] = x;
                setSize[x] += setSize[y];
            } else {
                p[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y])
                    rank[y]++;
            }
        }
    }
}

public class undetected {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        int[] rads = new int[n];
        int[][] coords = new int[n][2];
        
        for (int i = 0; i < n; i++) {
            coords[i][0] = scanner.nextInt();
            coords[i][1] = scanner.nextInt();
            rads[i] = scanner.nextInt();
        }
        
        UnionFind uf = new UnionFind(n + 2);
        int idx = 0;
        
        while (idx < n) {
            // Check left wall collision
            if (coords[idx][0] - rads[idx] < 0)
                uf.unionSet(0, idx + 2);
            // Check right wall collision
            if (coords[idx][0] + rads[idx] > 200)
                uf.unionSet(1, idx + 2);
            
            // Check intersection with previous circles
            for (int j = 0; j < idx; j++) {
                int dx = coords[idx][0] - coords[j][0];
                int dy = coords[idx][1] - coords[j][1];
                int rSum = rads[idx] + rads[j];
                
                if (dx * dx + dy * dy < rSum * rSum)
                    uf.unionSet(idx + 2, j + 2);
            }
            
            // Check if left and right walls are connected
            if (uf.isSameSet(0, 1))
                break;
                
            idx++;
        }
        
        System.out.println(idx);
        
        scanner.close();
    }
}