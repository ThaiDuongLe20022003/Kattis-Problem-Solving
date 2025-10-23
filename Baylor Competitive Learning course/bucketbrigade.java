import java.util.Scanner;

public class bucketbrigade {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while (sc.hasNextDouble()) {
            double n = sc.nextDouble();
            double v = sc.nextDouble();
            double x = sc.nextDouble();
            double f = sc.nextDouble();
            double t = sc.nextDouble();

            double loads = Math.ceil(v / x);
            double volPerLoad = v / loads;
            double result = (n + 2 * (loads - 1)) * (volPerLoad / f + t) + volPerLoad / f;
            System.out.println(result);
        }

        sc.close();
    }
}