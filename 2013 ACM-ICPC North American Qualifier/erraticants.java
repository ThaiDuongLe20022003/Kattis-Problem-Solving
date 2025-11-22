import java.util.*;
import java.io.*;

class Point {
    int x, y;
    
    Point(int x, int y) {
        this.x = x;
        this.y = y;
    }
    
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Point point = (Point) obj;
        return x == point.x && y == point.y;
    }
    
    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }
}

public class erraticants {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        br.readLine(); // Consume blank line
        
        for (int pathNum = 0; pathNum < n; pathNum++) {
            int s = Integer.parseInt(br.readLine());
            
            Map<Point, Set<Point>> adj = new HashMap<>();
            Point currentPos = new Point(0, 0);
            Point startNode = new Point(0, 0);
            
            for (int i = 0; i < s; i++) {
                char dirChar = br.readLine().charAt(0);
                
                Point nextPos = new Point(currentPos.x, currentPos.y);
                switch (dirChar) {
                    case 'N': nextPos.y++; break;
                    case 'E': nextPos.x++; break;
                    case 'S': nextPos.y--; break;
                    case 'W': nextPos.x--; break;
                }
                
                // Add bidirectional edges
                adj.computeIfAbsent(currentPos, k -> new HashSet<>()).add(nextPos);
                adj.computeIfAbsent(nextPos, k -> new HashSet<>()).add(currentPos);
                
                currentPos = nextPos;
            }
            Point foodLocation = currentPos;
            
            // BFS
            Map<Point, Integer> dist = new HashMap<>();
            Queue<Point> queue = new LinkedList<>();
            int shortestPath = -1;
            
            dist.put(startNode, 0);
            queue.offer(startNode);
            
            while (!queue.isEmpty()) {
                Point u = queue.poll();
                int d = dist.get(u);
                
                if (u.equals(foodLocation)) {
                    shortestPath = d;
                    break;
                }
                
                if (adj.containsKey(u)) {
                    for (Point v : adj.get(u)) {
                        if (!dist.containsKey(v)) {
                            dist.put(v, d + 1);
                            queue.offer(v);
                        }
                    }
                }
            }
            
            System.out.println(shortestPath);
            
            // Consume blank line if not last path
            if (pathNum < n - 1) {
                br.readLine();
            }
        }
    }
}