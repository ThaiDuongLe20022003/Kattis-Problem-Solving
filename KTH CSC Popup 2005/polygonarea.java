import java.util.Scanner;

public class polygonarea {
    static double polygonarea(double[][] points) {
        int n = points.length;
        double area = 0.0;
        for (int i = 0; i < n; i++) {
            int j = (i + 1) % n;
            area += (points[i][0] * points[j][1] - points[j][0] * points[i][1]);
        }
        return area / 2.0;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int tests = scanner.nextInt();
        while (tests != 0) {
            double[][] points = new double[tests][2];
            for (int i = 0; i < tests; i++) {
                points[i][0] = scanner.nextDouble();
                points[i][1] = scanner.nextDouble();
            }

            // Calculate area
            double area = polygonarea(points);
            String orientation = (area < 0) ? "CW" : "CCW";
            System.out.printf("%s %.1f%n", orientation, Math.abs(area));

            tests = scanner.nextInt();
        }
        scanner.close();
    }
}