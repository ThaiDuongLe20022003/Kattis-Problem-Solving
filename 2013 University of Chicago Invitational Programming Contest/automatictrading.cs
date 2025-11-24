using System;
using System.Collections.Generic;

public class SparseTable {
    private int[][] memo;
    private int[] logTwo;
    private int maxPow;
    
    public SparseTable(int[] arr) {
        int n = arr.Length;
        logTwo = new int[n + 1];
        for (int i = 2; i <= n; i++) {
            logTwo[i] = 1 + logTwo[i / 2];
        }
        maxPow = logTwo[n] + 1;
        memo = new int[maxPow][];
        for (int j = 0; j < maxPow; j++) {
            memo[j] = new int[n];
            for (int i = 0; i < n; i++) {
                if (i + (1 << j) - 1 < n) {
                    if (j == 0) {
                        memo[j][i] = arr[i];
                    } else {
                        memo[j][i] = Math.Min(memo[j - 1][i], memo[j - 1][i + (1 << (j - 1))]);
                    }
                }
            }
        }
    }
    
    public int Query(int l, int r) {
        if (l > r) return 0;
        int j = logTwo[r - l + 1];
        return Math.Min(memo[j][l], memo[j][r - (1 << j) + 1]);
    }
}

public class SuffixArray {
    private string s;
    private int N;
    private int gap;
    private int[] sa, pos, lcp, tmp;
    
    public SuffixArray(string str) {
        s = str;
        N = s.Length;
        sa = new int[N];
        pos = new int[N];
        lcp = new int[N];
        tmp = new int[N];
    }
    
    private bool SufCmp(int i, int j) {
        if (pos[i] != pos[j]) return pos[i] < pos[j];
        i += gap;
        j += gap;
        return (i < N && j < N) ? pos[i] < pos[j] : i > j;
    }
    
    public void BuildSA() {
        for (int i = 0; i < N; i++) {
            sa[i] = i;
            pos[i] = s[i];
        }
        for (gap = 1; ; gap *= 2) {
            Array.Sort(sa, (a, b) => SufCmp(a, b) ? -1 : 1);
            tmp[0] = 0;
            for (int i = 0; i < N - 1; i++) {
                tmp[i + 1] = tmp[i] + (SufCmp(sa[i], sa[i + 1]) ? 1 : 0);
            }
            for (int i = 0; i < N; i++) {
                pos[sa[i]] = tmp[i];
            }
            if (tmp[N - 1] == N - 1) break;
        }
    }
    
    public void BuildLCP() {
        for (int i = 0, k = 0; i < N; i++) {
            if (pos[i] != 0) {
                int j = sa[pos[i] - 1];
                while (i + k < N && j + k < N && s[i + k] == s[j + k]) k++;
                lcp[pos[i]] = k;
                if (k > 0) k--;
            }
        }
    }
    
    public int[] SA => sa;
    public int[] Pos => pos;
    public int[] LCP => lcp;
}

public class Program {
    public static void Main() {
        string s = Console.ReadLine();
        SuffixArray sa = new SuffixArray(s);
        sa.BuildSA();
        
        int[] inv = new int[s.Length];
        for (int i = 0; i < s.Length; i++) {
            inv[sa.SA[i]] = i;
        }
        
        sa.BuildLCP();
        
        int[] temp = new int[s.Length];
        for (int i = 0; i < s.Length; i++) {
            temp[i] = sa.LCP[i];
        }
        
        SparseTable st = new SparseTable(temp);
        
        int q = int.Parse(Console.ReadLine());
        for (int i = 0; i < q; i++) {
            string[] query = Console.ReadLine().Split();
            int pos1 = int.Parse(query[0]);
            int pos2 = int.Parse(query[1]);
            int p1 = inv[pos1];
            int p2 = inv[pos2];
            if (p1 > p2) {
                int tempSwap = p1;
                p1 = p2;
                p2 = tempSwap;
            }
            Console.WriteLine(st.Query(p1 + 1, p2));
        }
    }
}