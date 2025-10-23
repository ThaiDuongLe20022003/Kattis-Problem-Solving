import java.util.Scanner;

public class oddbinom {

    static int oneBits(long n) {
        n -= (n >> 1) & 0x5555555555555555L;
        n = (n & 0x3333333333333333L) + ((n >> 2) & 0x3333333333333333L);
        n = (n + (n >> 4)) & 0x0f0f0f0f0f0f0f0fL;
        return (int) ((n * 0x0101010101010101L) >>> 56);
    }

    static long odds(long n) {
        return n < 2 ? n : 3 * odds(n >> 1) + ((n % 2 != 0) ? (1L << oneBits(n - 1)) : 0L);
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        long n = scanner.nextLong();
        System.out.println(odds(n));
    }
}
