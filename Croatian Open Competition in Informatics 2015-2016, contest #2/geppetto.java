import java.util.*;

public class geppetto {
    static boolean works(Set<Pair<Integer, Integer>> s, int n) {
        Set<Integer> in = new HashSet<>();
        int i = 1;
        while (n > 0) {
            if ((n & 1) != 0) {
                in.add(i);
            }
            i++;
            n >>= 1;
        }

        for (Pair<Integer, Integer> p : s) {
            if (in.contains(p.getKey()) && in.contains(p.getValue())) {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int n = scanner.nextInt();
        int m = scanner.nextInt();

        Set<Pair<Integer, Integer>> v = new HashSet<>();
        for (int i = 0; i < m; i++) {
            int t1 = scanner.nextInt();
            int t2 = scanner.nextInt();
            if (t1 > t2) {
                int temp = t1;
                t1 = t2;
                t2 = temp;
            }
            v.add(new Pair<>(t1, t2));
        }

        int ans = 0;
        for (int i = 0; i < (1 << n); i++) {
            if (works(v, i)) {
                ans++;
            }
        }

        System.out.println(ans);
    }

    static class Pair<K, V> {
        private K key;
        private V value;

        public Pair(K key, V value) {
            this.key = key;
            this.value = value;
        }

        public K getKey() {
            return key;
        }

        public V getValue() {
            return value;
        }
    }
}