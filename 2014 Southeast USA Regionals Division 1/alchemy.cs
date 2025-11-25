using System;
using System.Collections.Generic;

public class Point {
    public int x, y;
    
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

public class Circle : IComparable<Circle> {
    public Point origin;
    public int radius;
    public int i;
    
    public Circle(Point origin, int radius, int i) {
        this.origin = origin;
        this.radius = radius;
        this.i = i;
    }
    
    public int CompareTo(Circle other) {
        if (radius != other.radius) return radius.CompareTo(other.radius);
        if (origin.x != other.origin.x) return origin.x.CompareTo(other.origin.x);
        return origin.y.CompareTo(other.origin.y);
    }
    
    public bool Encloses(Circle other) {
        return radius > other.radius && 
               SquaredDist(origin, other.origin) < radius * radius;
    }
    
    private static int SquaredDist(Point a, Point b) {
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
}

public class Program {
    public static void Main() {
        int n = int.Parse(Console.ReadLine());
        
        var circles = new Circle[n];
        var energy = new int[n + 1, 2];
        
        for (int i = 1; i <= n; i++) {
            var parts = Console.ReadLine().Split();
            int x = int.Parse(parts[0]);
            int y = int.Parse(parts[1]);
            int r = int.Parse(parts[2]);
            int a = int.Parse(parts[3]);
            int b = int.Parse(parts[4]);
            
            circles[i - 1] = new Circle(new Point(x, y), r, i);
            energy[i, 0] = a;
            energy[i, 1] = b;
        }
        
        Array.Sort(circles);
        
        int e = 0;
        var parent = new int[n + 1];
        var depth = new int[n + 1];
        var total = new int[n + 1];
        var peak = new (int, int)[n + 1];
        
        for (int i = n - 2; i >= 0; i--) {
            for (int j = i + 1; j < n; j++) {
                if (circles[j].Encloses(circles[i])) {
                    int c1 = circles[i].i, c2 = circles[j].i;
                    parent[c1] = c2;
                    depth[c1] = depth[c2] + 1;
                    
                    for (int d = 0; ; d++) {
                        if (peak[c1].Item1 < total[c1]) {
                            peak[c1] = (total[c1], d);
                        }
                        if (d == depth[c1]) break;
                        total[c1] += energy[c1, d & 1];
                    }
                    e += peak[c1].Item1;
                    break;
                }
            }
        }
        Console.WriteLine(e);
        
        var affected = new bool[n + 1];
        var drawn = new bool[n + 1];
        var skip = new bool[n + 1];
        
        for (int iter = 0; iter < n; iter++) {
            int j = -1;
            for (int i = 0; i < n; i++) {
                int c = circles[i].i;
                affected[c] = false;
                if (skip[c] || (depth[c] == peak[c].Item2 && !drawn[c])) {
                    if (parent[c] != 0) skip[parent[c]] = true;
                }
                if (skip[c]) continue;
                if (total[c] == peak[c].Item1 && !drawn[c] && (j < 0 || circles[j].i > c)) {
                    j = i;
                }
            }
            
            int c1 = circles[j].i;
            Console.Write(c1 + " ");
            drawn[c1] = true;
            affected[c1] = true;
            
            for (int i = n - 1; i >= 0; i--) {
                int c2 = circles[i].i;
                skip[c2] = false;
                if (parent[c2] != 0 && affected[parent[c2]]) {
                    affected[c2] = true;
                    depth[c2]--;
                    total[c2] -= energy[c2, depth[c2] & 1];
                }
            }
        }
        Console.WriteLine();
    }
}