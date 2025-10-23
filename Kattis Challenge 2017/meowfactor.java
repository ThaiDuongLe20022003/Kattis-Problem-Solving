import java.util.*;
import java.util.Map.Entry;

public class meowfactor {
    public static void main(String[] args) {
        // file();
        fast();

        Scanner sc = new Scanner(System.in);
        long n = sc.nextLong();

        Map<Long, Long> m = factor(n);
        long ans = 1;
        for (Entry<Long, Long> entry : m.entrySet()) {
            long prime = entry.getKey();
            long count = entry.getValue();

            while (count >= 9) {
                count -= 9;
                ans *= prime;
            }
        }
        System.out.println(ans);
    }

    static Map<Long, Long> factor(long n) {
        Map<Long, Long> m = new HashMap<>();
        for (long i = 2; i <= Math.min((long) Math.sqrt(n), (long) 100000); i++) {
            while (n % i == 0) {
                m.put(i, m.getOrDefault(i, 0L) + 1);
                n /= i;
            }
        }
        if (n > 1) {
            m.put(n, m.getOrDefault(n, 0L) + 1);
        }
        return m;
    }

    static void fast() {
        // Fast I/O setup can be added here if needed.
    }

    static void file() {
        // File I/O setup can be added here if needed.
    }
}