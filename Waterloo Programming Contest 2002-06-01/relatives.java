import java.io.*;
import java.util.*;

public class relatives {
    public static void main(String[] args) {
        // file();
        // fast();

        Scanner sc = new Scanner(System.in);
        long n;
        while (sc.hasNext()) {
            n = sc.nextLong();
            if (n == 0) {
                break;
            }
            System.out.println(phi(n));
        }
    }

    static long phi(long n) {
        long result = n;
        for (long i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                while (n % i == 0) {
                    n /= i;
                }
                result -= result / i;
            }
        }

        if (n > 1) {
            result -= result / n;
        }

        return result;
    }

    // Other utility functions can be added here
}