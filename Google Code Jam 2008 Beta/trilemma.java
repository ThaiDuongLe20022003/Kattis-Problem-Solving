import java.util.Scanner;
import java.util.Vector;
import java.util.Collections;

class Point {
    int x, y;

    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public class trilemma {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        for (int i = 1; i <= n; i++) {
            System.out.print("Case #" + i + ": ");
            solve(sc);
        }
    }

    static int dist(Point p1, Point p2) {
        int d1 = p1.x - p2.x;
        int d2 = p1.y - p2.y;
        return d1 * d1 + d2 * d2;
    }

    static boolean colinear(Point p1, Point p2, Point p3) {
        int a = p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y);
        return (a == 0);
    }

    static void solve(Scanner sc) {
        Point p1 = new Point(sc.nextInt(), sc.nextInt());
        Point p2 = new Point(sc.nextInt(), sc.nextInt());
        Point p3 = new Point(sc.nextInt(), sc.nextInt());

        if (colinear(p1, p2, p3)) {
            System.out.println("not a triangle");
            return;
        }

        Vector<Integer> d = new Vector<Integer>();
        d.add(dist(p1, p2));
        d.add(dist(p3, p2));
        d.add(dist(p1, p3));
        Collections.sort(d);

        boolean isosceles = false;
        if (d.get(0).equals(d.get(1)) || d.get(1).equals(d.get(2))) {
            isosceles = true;
        }

        if (isosceles) {
            System.out.print("isosceles ");
        } else {
            System.out.print("scalene ");
        }

        if (d.get(0) + d.get(1) == d.get(2)) {
            System.out.print("right ");
        }
        if (d.get(0) + d.get(1) > d.get(2)) {
            System.out.print("acute ");
        }
        if (d.get(0) + d.get(1) < d.get(2)) {
            System.out.print("obtuse ");
        }

        System.out.println("triangle");
    }
}