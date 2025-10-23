import java.util.Scanner;

class Vertex {
    int x, y;
}

public class convexpolygonarea {
    static int det(Vertex v1, Vertex v2) {
        return v1.x * v2.y - v1.y * v2.x;
    }

    static void findArea(Vertex[] vertices, int v) {
        int sum = 0;
        for (int i = 0; i < v - 1; i++) {
            sum += det(vertices[i], vertices[i + 1]);
        }
        sum += det(vertices[v - 1], vertices[0]);
        if ((sum & 1) != 0) {
            System.out.printf("%.1f\n", sum / 2.0);
        } else {
            System.out.printf("%d\n", sum >> 1);
        }
    }

    static void readVertices(Vertex[] vertices, int v, Scanner scanner) {
        for (int i = 0; i < v; i++) {
            vertices[i] = new Vertex();
            vertices[i].x = scanner.nextInt();
            vertices[i].y = scanner.nextInt();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        while (n-- > 0) {
            int v = scanner.nextInt();
            Vertex[] vertices = new Vertex[v];
            readVertices(vertices, v, scanner);
            findArea(vertices, v);
        }
        scanner.close();
    }
}