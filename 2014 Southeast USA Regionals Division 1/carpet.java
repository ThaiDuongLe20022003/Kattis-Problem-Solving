import java.util.Scanner;

public class carpet {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        double a = scanner.nextDouble();
        double b = scanner.nextDouble();
        double c = scanner.nextDouble();

        double s = (a + b + c) / 2;
        double area = Math.sqrt(s * (s - a) * (s - b) * (s - c));
        double t = a * a + b * b + c * c;
        double carpet = (Math.sqrt(3) / 4 * t + 3 * area) / 2;
        
        boolean validTriangle = (a + b >= c && a + c >= b && b + c >= a);
        double minSide = Math.sqrt(carpet * 4 / Math.sqrt(3));
        double maxSide = Math.max(a, Math.max(b, c));
        boolean meetsCondition = (minSide >= maxSide);
        
        if (validTriangle && meetsCondition) {
            System.out.printf("%.3f\n", carpet);
        } else {
            System.out.println("-1");
        }
    }
}