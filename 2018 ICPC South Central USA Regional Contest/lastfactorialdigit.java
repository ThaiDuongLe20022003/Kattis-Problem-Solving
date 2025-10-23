import java.util.Scanner;

public class lastfactorialdigit {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int t = scanner.nextInt();
        while (t-- > 0) {
            int x = scanner.nextInt();
            System.out.println((x >= 5) ? 0 : fact(x));
        }
    }

    static int fact(int n) {
        if (n < 2) return 1;
        return (n % 10 * fact(n - 1)) % 10;
    }
}