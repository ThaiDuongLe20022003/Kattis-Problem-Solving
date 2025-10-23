import java.util.Scanner;

public class parking {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int[] cijena = new int[4];
        int[] koliko = new int[100];

        for (int i = 1; i <= 3; ++i) {
            cijena[i] = scanner.nextInt();
        }
        for (int i = 1; i <= 3; ++i) {
            int t1 = scanner.nextInt();
            int t2 = scanner.nextInt();
            for (int t = t1; t < t2; ++t) {
                ++koliko[t];
            }
        }

        int ukupno = 0;
        for (int t = 0; t < 100; ++t) {
            ukupno += koliko[t] * cijena[koliko[t]];
        }
        System.out.println(ukupno);
        scanner.close();
    }
}