import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

class closestpair1 {
    static class Point {
        double x, y;

        Point(double x, double y) {
            this.x = x;
            this.y = y;
        }
    }

    static Point[] points = new Point[100001];

    static double squaredDistance(Point p1, Point p2) {
        return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
    }

    static void quickSort(Point[] arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    static int partition(Point[] arr, int low, int high) {
        Point pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (compare(arr[j], pivot) < 0) {
                i++;
                Point temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Point temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }

    static int compare(Point p1, Point p2) {
        if (p1.x != p2.x) {
            return Double.compare(p1.x, p2.x);
        }
        return Double.compare(p1.y, p2.y);
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;
        while ((line = br.readLine()) != null && !line.isEmpty()) {
            int n = Integer.parseInt(line);
            if (n == 0) break;

            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                double x = Double.parseDouble(st.nextToken());
                double y = Double.parseDouble(st.nextToken());
                points[i] = new Point(x, y);
            }

            quickSort(points, 0, n - 1);

            Point res1 = points[0];
            Point res2 = points[1];
            double minDist = squaredDistance(res1, res2);

            for (int i = 2; i < n; i++) {
                Point p = points[i];
                for (int j = i - 1; j >= 0; j--) {
                    double dist = squaredDistance(p, points[j]);
                    if (dist < minDist) {
                        minDist = dist;
                        res1 = points[j];
                        res2 = p;
                    } else if ((p.x - points[j].x) > minDist) {
                        break;
                    }
                }
            }
            System.out.printf("%.2f %.2f %.2f %.2f\n", res1.x, res1.y, res2.x, res2.y);
        }
        br.close();
    }
}