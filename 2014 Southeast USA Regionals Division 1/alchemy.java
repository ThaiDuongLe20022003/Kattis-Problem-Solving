import java.util.*;
import java.io.*;

class Point {
    int x, y;
    
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

class Circle implements Comparable<Circle> {
    Point origin;
    int radius;
    int i;
    
    Circle(Point origin, int radius, int i) {
        this.origin = origin;
        this.radius = radius;
        this.i = i;
    }
    
    @Override
    public int compareTo(Circle other) {
        if (radius != other.radius) return Integer.compare(radius, other.radius);
        if (origin.x != other.origin.x) return Integer.compare(origin.x, other.origin.x);
        return Integer.compare(origin.y, other.origin.y);
    }
    
    boolean encloses(Circle other) {
        return radius > other.radius && 
               squaredDist(origin, other.origin) < radius * radius;
    }
    
    private static int squaredDist(Point a, Point b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
}

public class alchemy {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        
        Circle[] circles = new Circle[n];
        int[][] energy = new int[n + 1][2];
        
        for (int i = 1; i <= n; i++) {
            StringTokenizer st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            int r = Integer.parseInt(st.nextToken());
            int a = Integer.parseInt(st.nextToken());
            int b = Integer.parseInt(st.nextToken());
            
            circles[i - 1] = new Circle(new Point(x, y), r, i);
            energy[i][0] = a;
            energy[i][1] = b;
        }
        
        Arrays.sort(circles);
        
        int e = 0;
        int[] parent = new int[n + 1];
        int[] depth = new int[n + 1];
        int[] total = new int[n + 1];
        int[][] peak = new int[n + 1][2];
        
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (circles[j].encloses(circles[i])) {
                    int c1 = circles[i].i, c2 = circles[j].i;
                    parent[c1] = c2;
                    depth[c1] = depth[c2] + 1;
                    
                    for (int d = 0; ; d++) {
                        if (peak[c1][0] < total[c1]) {
                            peak[c1][0] = total[c1];
                            peak[c1][1] = d;
                        }
                        if (d == depth[c1]) break;
                        total[c1] += energy[c1][d & 1];
                    }
                    e += peak[c1][0];
                    break;
                }
            }
        }
        System.out.println(e);
        
        boolean[] affected = new boolean[n + 1];
        boolean[] drawn = new boolean[n + 1];
        boolean[] skip = new boolean[n + 1];
        
        for (int iter = 0; iter < n; iter++) {
            int j = -1;
            for (int i = 0; i < n; i++) {
                int c = circles[i].i;
                affected[c] = false;
                if (skip[c] || (depth[c] == peak[c][1] && !drawn[c])) {
                    if (parent[c] != 0) skip[parent[c]] = true;
                }
                if (skip[c]) continue;
                if (total[c] == peak[c][0] && !drawn[c] && (j < 0 || circles[j].i > c)) {
                    j = i;
                }
            }
            
            int c1 = circles[j].i;
            System.out.print(c1 + " ");
            drawn[c1] = true;
            affected[c1] = true;
            
            for (int i = n - 1; i >= 0; i--) {
                int c2 = circles[i].i;
                skip[c2] = false;
                if (parent[c2] != 0 && affected[parent[c2]]) {
                    affected[c2] = true;
                    depth[c2]--;
                    total[c2] -= energy[c2][depth[c2] & 1];
                }
            }
        }
        System.out.println();
    }
}