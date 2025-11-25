import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class stampstamp {

    static class Pt {
        int x, y;

        public Pt(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pt pt = (Pt) o;
            return x == pt.x && y == pt.y;
        }

        @Override
        public int hashCode() {
            return 31 * x + y;
        }
    }

    // Function to compute the cross product (orientation)
    // > 0 for counter-clockwise, < 0 for clockwise, = 0 for collinear
    static long crossProduct(Pt a, Pt b, Pt c) {
        return 1L * (b.x - a.x) * (c.y - a.y) - 1L * (b.y - a.y) * (c.x - a.x);
    }

    // Graham Scan for Convex Hull
    static void convexHull(List<Pt> a) {
        if (a.size() <= 2) return;

        // 1. Find the point with the smallest y-coordinate (and smallest x in case of ties)
        Pt p0 = a.get(0);
        for (int i = 1; i < a.size(); ++i) {
            Pt current = a.get(i);
            if (current.y < p0.y || (current.y == p0.y && current.x < p0.x)) {
                p0 = current;
            }
        }

        // 2. Sort points by polar angle with respect to p0
        Pt finalP0 = p0;
        Collections.sort(a, new Comparator<Pt>() {
            @Override
            public int compare(Pt a, Pt b) {
                long cp = crossProduct(finalP0, a, b);
                if (cp != 0)
                    return cp > 0 ? -1 : 1; // Counter-clockwise order
                // Collinear case: sort by distance from p0
                long distA = 1L * (finalP0.x - a.x) * (finalP0.x - a.x) + 1L * (finalP0.y - a.y) * (finalP0.y - a.y);
                long distB = 1L * (finalP0.x - b.x) * (finalP0.x - b.x) + 1L * (finalP0.y - b.y) * (finalP0.y - b.y);
                return Long.compare(distA, distB);
            }
        });

        // 3. Build the hull
        List<Pt> st = new ArrayList<>();
        for (Pt p : a) {
            while (st.size() >= 2 && crossProduct(st.get(st.size() - 2), st.get(st.size() - 1), p) <= 0) {
                st.remove(st.size() - 1);
            }
            st.add(p);
        }

        a.clear();
        a.addAll(st);
    }

    // Function to calculate GCD
    static int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    public static void solve() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);

        String[] line = br.readLine().split(" ");
        int N = Integer.parseInt(line[0]); // rows
        int M = Integer.parseInt(line[1]); // columns

        boolean[][] grid = new boolean[M][N]; // grid[x][y]
        List<Pt> points = new ArrayList<>();
        int number_of_points_total = 0;

        // Read input and transform coordinates: (row, col) -> (x, y) where x=col, y=N-1-row
        for (int j = 0; j < N; ++j) {
            String row = br.readLine();
            for (int i = 0; i < M; ++i) {
                if (row.charAt(i) == '#') {
                    grid[i][N - 1 - j] = true;
                    points.add(new Pt(i, N - 1 - j));
                    number_of_points_total++;
                }
            }
        }

        if (number_of_points_total == 0) {
            pw.println(0);
            pw.close();
            return;
        }
        if (number_of_points_total <= 2) {
            pw.println(1);
            pw.close();
            return;
        }

        // Calculate Convex Hull to reduce the number of points to check
        convexHull(points);

        int num_hull_points = points.size();
        if (num_hull_points <= 2) {
            pw.println(1);
            pw.close();
            return;
        }

        // Map to store the minimum GCD for each unique coprime direction vector (cx, cy)
        Map<Pt, Integer> minGForDir = new HashMap<>();
        // List to store the unique coprime direction vectors that appear twice
        List<Pt> seenTwiceDirs = new ArrayList<>();

        // Iterate over the edges of the convex hull
        for (int i = 0; i < num_hull_points; ++i) {
            Pt p = points.get(i);
            Pt q = points.get((i + 1) % num_hull_points);

            // Calculate the direction vector (dx, dy)
            int dx = q.x - p.x;
            int dy = q.y - p.y;

            // Calculate GCD to find the coprime direction vector (cx, cy)
            int commonDivisor = gcd(Math.abs(dx), Math.abs(dy));
            int g = commonDivisor;
            
            // Normalize the direction vector to coprime (cx, cy)
            int cx = dx / g;
            int cy = dy / g;

            // Ensure the coprime vector is canonical (e.g., first non-zero component is positive)
            if (cx < 0 || (cx == 0 && cy < 0)) {
                cx = -cx;
                cy = -cy;
            }
            
            Pt cpair = new Pt(cx, cy);

            if (minGForDir.containsKey(cpair)) {
                // If seen before, this is the second (or more) time.
                // Update the minimum g (which corresponds to the maximum shift k)
                if (minGForDir.get(cpair) == -1) {
                    // First time seeing the second instance
                    seenTwiceDirs.add(cpair);
                    minGForDir.put(cpair, g);
                } else {
                    minGForDir.put(cpair, Math.min(minGForDir.get(cpair), g));
                }
            } else {
                // First time seeing this direction
                minGForDir.put(cpair, -1); // Use -1 as a sentinel for "seen once"
            }
        }

        int best_score = number_of_points_total; // Initialize with the worst case

        // Iterate over all possible relative shifts (dx, dy)
        for (Pt cpair : seenTwiceDirs) {
            int cx = cpair.x;
            int cy = cpair.y;
            int max_k = minGForDir.get(cpair);

            for (int k = 1; k <= max_k; ++k) {
                int dx = k * cx;
                int dy = k * cy;
                int current_score = 0;
                boolean is_valid = true;
                
                // The complexity of this part is O(N*M) total over all starting points.
                // Total complexity: O(H*W * N*M) = O(N^2 M^2).
                
                // Iterate over all cells (x, y) in the grid
                for (int x = 0; x < M; ++x) {
                    for (int y = 0; y < N; ++y) {
                        // Check if (x, y) is the start of a run
                        // A cell (x, y) is the start of a run if:
                        // 1. It is marked.
                        // 2. The cell before it on the line is unmarked or outside the grid.
                        
                        boolean is_marked = grid[x][y];
                        
                        // Check the cell before: (x - dx, y - dy)
                        int prev_x = x - dx;
                        int prev_y = y - dy;
                        boolean prev_is_marked = (prev_x >= 0 && prev_x < M && prev_y >= 0 && prev_y < N) && grid[prev_x][prev_y];
                        
                        if (is_marked && !prev_is_marked) {
                            // This is the start of a run. Calculate the run length.
                            int run_length = 0;
                            int cur_x = x;
                            int cur_y = y;
                            
                            while (cur_x >= 0 && cur_x < M && cur_y >= 0 && cur_y < N && grid[cur_x][cur_y]) {
                                run_length++;
                                cur_x += dx;
                                cur_y += dy;
                            }
                            
                            if (run_length == 1) {
                                is_valid = false;
                                break;
                            }
                            current_score += (run_length + 1) / 2;
                        }
                    }
                    if (!is_valid) break;
                }
                
                if (is_valid) {
                    best_score = Math.min(best_score, current_score);
                }
            }
        }

        pw.println(best_score);
        pw.close();
    }

    public static void main(String[] args) {
        try {
            solve();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}