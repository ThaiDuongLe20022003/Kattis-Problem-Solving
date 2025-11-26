using System;

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
    
    public int FindSet(int i) {
        return (p[i] == i) ? i : (p[i] = FindSet(p[i]));
    }
    
    public bool IsSameSet(int i, int j) {
        return FindSet(i) == FindSet(j);
    }
    
    public void UnionSet(int i, int j) {
        if (!IsSameSet(i, j)) {
            numSets--;
            int x = FindSet(i);
            int y = FindSet(j);
            
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

class Program {
    static void Main() {
        int n = int.Parse(Console.ReadLine());
        int[] rads = new int[n];
        Tuple<int, int>[] coords = new Tuple<int, int>[n];
        
        for (int i = 0; i < n; i++) {
            string[] parts = Console.ReadLine().Split();
            int x = int.Parse(parts[0]);
            int y = int.Parse(parts[1]);
            int r = int.Parse(parts[2]);
            rads[i] = r;
            coords[i] = Tuple.Create(x, y);
        }
        
        UnionFind uf = new UnionFind(n + 2);
        int idx = 0;
        
        while (idx < n) {
            // Check left wall collision
            if (coords[idx].Item1 - rads[idx] < 0)
                uf.UnionSet(0, idx + 2);
            // Check right wall collision
            if (coords[idx].Item1 + rads[idx] > 200)
                uf.UnionSet(1, idx + 2);
            
            // Check intersection with previous circles
            for (int j = 0; j < idx; j++) {
                int dx = coords[idx].Item1 - coords[j].Item1;
                int dy = coords[idx].Item2 - coords[j].Item2;
                int rSum = rads[idx] + rads[j];
                
                if (dx * dx + dy * dy < rSum * rSum)
                    uf.UnionSet(idx + 2, j + 2);
            }
            
            // Check if left and right walls are connected
            if (uf.IsSameSet(0, 1))
                break;
                
            idx++;
        }
        
        Console.WriteLine(idx);
    }
}