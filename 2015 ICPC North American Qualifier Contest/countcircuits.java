import java.util.*;
import java.io.*;

public class countcircuits {
    static class Pair {
        int first, second;
        Pair(int first, int second) {
            this.first = first;
            this.second = second;
        }
        
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair pair = (Pair) o;
            return first == pair.first && second == pair.second;
        }
        
        @Override
        public int hashCode() {
            return Objects.hash(first, second);
        }
    }
    
    static void generate(List<Pair> v, Map<Pair, Integer> map) {
        int n = v.size();
        for (int i = 1; i < (1 << n); i++) {
            Pair sum = new Pair(0, 0);
            for (int j = 0; j < n; j++) {
                if (((1 << j) & i) != 0) {
                    sum.first += v.get(j).first;
                    sum.second += v.get(j).second;
                }
            }
            map.put(sum, map.getOrDefault(sum, 0) + 1);
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        List<Pair> v1 = new ArrayList<>();
        List<Pair> v2 = new ArrayList<>();
        
        for (int i = 0; i < n; i++) {
            int first = scanner.nextInt();
            int second = scanner.nextInt();
            if (i % 2 == 0) {
                v1.add(new Pair(first, second));
            } else {
                v2.add(new Pair(first, second));
            }
        }
        
        Map<Pair, Integer> set1 = new HashMap<>();
        Map<Pair, Integer> set2 = new HashMap<>();
        
        generate(v1, set1);
        generate(v2, set2);
        
        long ans = 0;
        
        for (Map.Entry<Pair, Integer> entry : set1.entrySet()) {
            Pair p = entry.getKey();
            Pair target = new Pair(-p.first, -p.second);
            if (set2.containsKey(target)) {
                ans += entry.getValue() * set2.get(target);
            }
        }
        
        // Add empty subsets
        Pair zero = new Pair(0, 0);
        if (set1.containsKey(zero)) ans += set1.get(zero);
        if (set2.containsKey(zero)) ans += set2.get(zero);
        
        System.out.println(ans);
        
        scanner.close();
    }
}