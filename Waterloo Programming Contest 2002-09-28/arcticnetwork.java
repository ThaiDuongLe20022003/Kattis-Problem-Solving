import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

class Point {
    int x, y;

    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

class Edge implements Comparable<Edge> {
    int p1, p2;
    double dist;

    public Edge(int p1, int p2, double dist) {
        this.p1 = p1;
        this.p2 = p2;
        this.dist = dist;
    }

    @Override
    public int compareTo(Edge other) {
        return Double.compare(this.dist, other.dist);
    }
}

public class arcticnetwork {
    public static double dist(Point p1, Point p2) {
        return Math.sqrt(Math.pow(p1.x - p2.x, 2) + Math.pow(p1.y - p2.y, 2));
    }

    public static int find(int[] disjoint, int a) {
        if (disjoint[a] == -1) {
            return a;
        }

        disjoint[a] = find(disjoint, disjoint[a]);
        return disjoint[a];
    }

    public static void join(int[] disjoint, int a, int b) {
        a = find(disjoint, a);
        b = find(disjoint, b);

        if (a == b) {
            return;
        }

        disjoint[a] = b;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int cases = scanner.nextInt();

        while (cases-- > 0) {
            int sat = scanner.nextInt();
            int out = scanner.nextInt();

            List<Point> points = new ArrayList<>();
            for (int i = 0; i < out; i++) {
                int x = scanner.nextInt();
                int y = scanner.nextInt();
                points.add(new Point(x, y));
            }

            List<Edge> edges = new ArrayList<>();
            for (int i = 0; i < points.size() - 1; i++) {
                for (int j = i + 1; j < points.size(); j++) {
                    double d = dist(points.get(i), points.get(j));
                    edges.add(new Edge(i, j, d));
                }
            }

            Collections.sort(edges);

            int[] disjoint = new int[out];
            Arrays.fill(disjoint, -1);
            
            List<Double> kept = new ArrayList<>();
            for (Edge edge : edges) {
                if (find(disjoint, edge.p1) != find(disjoint, edge.p2)) {
                    join(disjoint, edge.p1, edge.p2);
                    kept.add(edge.dist);
                }
            }

            for (int i = 1; i < sat; i++) {
                kept.remove(kept.size() - 1);
            }

            System.out.printf("%.2f%n", kept.get(kept.size() - 1));
        }
    }
}