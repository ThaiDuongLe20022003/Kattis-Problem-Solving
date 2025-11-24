import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

public class unrealestate {

    private static final double EPS = 1e-9;

    // Custom comparison function for doubles
    private static int compareDouble(double x, double y) {
        if (Math.abs(x - y) < EPS) return 0;
        return x < y ? -1 : 1;
    }

    // Segment Tree Implementation
    static class SegmentTree {
        private int n;
        private List<Double> yCoords;
        private int[] count;
        private double[] length;

        public SegmentTree(List<Double> yUnique) {
            this.yCoords = yUnique;
            this.n = yCoords.size();
            // A safe size for a segment tree on n-1 leaves is 4 * n
            count = new int[4 * n];
            length = new double[4 * n];
        }

        // Helper to update the length of a node
        private void updateLength(int node, int start, int end) {
            if (count[node] > 0) {
                // If count > 0, the entire segment [yCoords[start], yCoords[end]] is covered
                length[node] = yCoords.get(end) - yCoords.get(start);
            } else if (start + 1 < end) {
                // If count == 0 and it's not a leaf, sum up children's lengths
                length[node] = length[2 * node] + length[2 * node + 1];
            } else {
                // If count == 0 and it's a leaf, length is 0
                length[node] = 0.0;
            }
        }

        // Update the segment tree for a given y-interval [y1_idx, y2_idx)
        public void update(int node, int start, int end, int y1Idx, int y2Idx, int delta) {
            // [start, end] is the index range of yCoords for the current node
            // [y1Idx, y2Idx] is the index range of yCoords for the update interval

            // No overlap
            if (start >= y2Idx || end <= y1Idx) {
                return;
            }

            // Full overlap
            if (start >= y1Idx && end <= y2Idx) {
                count[node] += delta;
                updateLength(node, start, end);
                return;
            }

            // Partial overlap, recurse
            int mid = start + (end - start) / 2;
            update(2 * node, start, mid, y1Idx, y2Idx, delta);
            update(2 * node + 1, mid, end, y1Idx, y2Idx, delta);

            // After recursion, update the current node's length
            updateLength(node, start, end);
        }

        public double getTotalCoveredLength() {
            return length[1];
        }
    }

    // Event structure for the sweep line
    static class Event {
        public double x;
        public double y1, y2;
        public int type; // +1 for start of rectangle, -1 for end

        public Event(double x, double y1, double y2, int type) {
            this.x = x;
            this.y1 = y1;
            this.y2 = y2;
            this.type = type;
        }
    }

    public static void solve() throws Exception {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter pw = new PrintWriter(System.out);
        String line;

        while ((line = br.readLine()) != null) {
            int n;
            try {
                n = Integer.parseInt(line.trim());
            } catch (NumberFormatException e) {
                continue;
            }

            if (n == 0) break;

            List<Event> events = new ArrayList<>();
            List<Double> yCoords = new ArrayList<>();

            for (int i = 0; i < n; i++) {
                StringTokenizer st = new StringTokenizer(br.readLine());
                double x1 = Double.parseDouble(st.nextToken());
                double y1 = Double.parseDouble(st.nextToken());
                double x2 = Double.parseDouble(st.nextToken());
                double y2 = Double.parseDouble(st.nextToken());

                // Ensure x1 < x2 and y1 < y2
                if (compareDouble(x1, x2) > 0) { double temp = x1; x1 = x2; x2 = temp; }
                if (compareDouble(y1, y2) > 0) { double temp = y1; y1 = y2; y2 = temp; }

                // Ignore zero-area rectangles
                if (compareDouble(x1, x2) == 0 || compareDouble(y1, y2) == 0) continue;

                // Start event
                events.add(new Event(x1, y1, y2, 1));
                // End event
                events.add(new Event(x2, y1, y2, -1));

                yCoords.add(y1);
                yCoords.add(y2);
            }

            if (events.isEmpty()) {
                pw.printf("%.2f\n", 0.0);
                continue;
            }

            // 1. Sort and unique y-coordinates
            Collections.sort(yCoords, (a, b) -> compareDouble(a, b));
            List<Double> yUnique = new ArrayList<>();
            if (!yCoords.isEmpty()) {
                yUnique.add(yCoords.get(0));
                for (int i = 1; i < yCoords.size(); i++) {
                    if (compareDouble(yCoords.get(i), yCoords.get(i - 1)) != 0) {
                        yUnique.add(yCoords.get(i));
                    }
                }
            }

            // Create a map for quick index lookup of y-coordinates
            Map<Double, Integer> yToIndex = new HashMap<>();
            for (int i = 0; i < yUnique.size(); i++) {
                yToIndex.put(yUnique.get(i), i);
            }

            // 2. Sort x-events
            Collections.sort(events, new Comparator<Event>() {
                @Override
                public int compare(Event a, Event b) {
                    int cmpX = compareDouble(a.x, b.x);
                    if (cmpX != 0) {
                        return cmpX;
                    }
                    // Tie-breaking: process start events before end events (type +1 before -1)
                    return b.type - a.type;
                }
            });

            // 3. Initialize Segment Tree
            SegmentTree st = new SegmentTree(yUnique);

            double totalArea = 0.0;
            double lastX = events.get(0).x;

            // 4. Sweep line
            for (Event event : events) {
                double currentX = event.x;

                // Calculate area of the strip between lastX and currentX
                double dx = currentX - lastX;
                if (compareDouble(dx, 0.0) > 0) {
                    // st.getTotalCoveredLength() is the total length of the union of y-intervals
                    totalArea += st.getTotalCoveredLength() * dx;
                }

                // Update the segment tree for the current event
                int y1Idx = yToIndex.get(event.y1);
                int y2Idx = yToIndex.get(event.y2);
                
                // The update range is [y1Idx, y2Idx) on the yUnique indices.
                st.update(1, 0, st.yCoords.size() - 1, y1Idx, y2Idx, event.type);

                lastX = currentX;
            }

            pw.printf("%.2f\n", totalArea);
        }
        pw.flush();
    }

    public static void main(String[] args) throws Exception {
        solve();
    }
}