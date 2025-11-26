using System;
using System.Collections.Generic;

class Program {
    static void Generate(List<(int, int)> v, Dictionary<(int, int), int> map) {
        int n = v.Count;
        for (int i = 1; i < (1 << n); i++) {
            (int, int) sum = (0, 0);
            for (int j = 0; j < n; j++) {
                if (((1 << j) & i) != 0) {
                    sum.Item1 += v[j].Item1;
                    sum.Item2 += v[j].Item2;
                }
            }
            if (map.ContainsKey(sum)) {
                map[sum]++;
            } else {
                map[sum] = 1;
            }
        }
    }

    static void Main() {
        int n = int.Parse(Console.ReadLine());
        
        var v1 = new List<(int, int)>();
        var v2 = new List<(int, int)>();
        
        for (int i = 0; i < n; i++) {
            string[] parts = Console.ReadLine().Split();
            int first = int.Parse(parts[0]);
            int second = int.Parse(parts[1]);
            
            if (i % 2 == 0) {
                v1.Add((first, second));
            } else {
                v2.Add((first, second));
            }
        }
        
        var set1 = new Dictionary<(int, int), int>();
        var set2 = new Dictionary<(int, int), int>();
        
        Generate(v1, set1);
        Generate(v2, set2);
        
        long ans = 0;
        
        foreach (var pair in set1) {
            var p = pair.Key;
            var target = (-p.Item1, -p.Item2);
            if (set2.ContainsKey(target)) {
                ans += pair.Value * set2[target];
            }
        }
        
        // Add empty subsets
        var zero = (0, 0);
        if (set1.ContainsKey(zero)) ans += set1[zero];
        if (set2.ContainsKey(zero)) ans += set2[zero];
        
        Console.WriteLine(ans);
    }
}