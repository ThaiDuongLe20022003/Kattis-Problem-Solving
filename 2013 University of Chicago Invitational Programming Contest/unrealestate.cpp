#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <map>

using namespace std;

// Constants for floating point comparison
const double EPS = 1e-9;

// Custom comparison function for doubles
int compare_double(double x, double y) {
    if (fabs(x - y) < EPS) return 0;
    return x < y ? -1 : 1;
}

// Segment Tree Implementation
// The segment tree will operate on the discrete y-coordinates.
struct SegmentTree {
    int n;
    vector<double> y_coords;
    vector<int> count; // Number of active rectangles covering the segment
    vector<double> length; // Length of the covered segment

    SegmentTree(const vector<double>& y_unique) : y_coords(y_unique) {
        n = y_coords.size();
        // The tree will have nodes for n-1 elementary intervals
        // A safe size for a segment tree on n-1 leaves is 4 * (n-1)
        count.resize(4 * n, 0);
        length.resize(4 * n, 0.0);
    }

    // Helper to update the length of a node
    void update_length(int node, int start, int end) {
        if (count[node] > 0) {
            // If count > 0, the entire segment [y_coords[start], y_coords[end]] is covered
            length[node] = y_coords[end] - y_coords[start];
        } else if (start + 1 < end) {
            // If count == 0 and it's not a leaf, sum up children's lengths
            length[node] = length[2 * node] + length[2 * node + 1];
        } else {
            // If count == 0 and it's a leaf, length is 0
            length[node] = 0.0;
        }
    }

    // Update the segment tree for a given y-interval [y1, y2]
    void update(int node, int start, int end, int y1_idx, int y2_idx, int delta) {
        // [start, end] is the index range of y_coords for the current node
        // [y1_idx, y2_idx] is the index range of y_coords for the update interval

        // No overlap
        if (start >= y2_idx || end <= y1_idx) {
            return;
        }

        // Full overlap
        if (start >= y1_idx && end <= y2_idx) {
            count[node] += delta;
            update_length(node, start, end);
            return;
        }

        // Partial overlap, recurse
        int mid = start + (end - start) / 2;
        update(2 * node, start, mid, y1_idx, y2_idx, delta);
        update(2 * node + 1, mid, end, y1_idx, y2_idx, delta);

        // After recursion, update the current node's length
        update_length(node, start, end);
    }
};

// Event structure for the sweep line
struct Event {
    double x;
    double y1, y2;
    int type; // +1 for start of rectangle, -1 for end

    bool operator<(const Event& other) const {
        if (compare_double(x, other.x) != 0) {
            return compare_double(x, other.x) < 0;
        }
        // Tie-breaking: process start events before end events
        return type > other.type;
    }
};

void solve() {
    int n;
    while (cin >> n && n != 0) {
        vector<Event> events;
        vector<double> y_coords;
        events.reserve(2 * n);
        y_coords.reserve(2 * n);

        for (int i = 0; i < n; i++) {
            double x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            // Ensure x1 < x2 and y1 < y2
            if (compare_double(x1, x2) > 0) swap(x1, x2);
            if (compare_double(y1, y2) > 0) swap(y1, y2);

            // Ignore zero-area rectangles
            if (compare_double(x1, x2) == 0 || compare_double(y1, y2) == 0) continue;

            // Start event
            events.push_back({x1, y1, y2, 1});
            // End event
            events.push_back({x2, y1, y2, -1});

            y_coords.push_back(y1);
            y_coords.push_back(y2);
        }

        if (events.empty()) {
            cout << 0.00 << "\n";
            continue;
        }

        // 1. Sort and unique y-coordinates
        sort(y_coords.begin(), y_coords.end(), [](double a, double b) {
            return compare_double(a, b) < 0;
        });
        y_coords.erase(unique(y_coords.begin(), y_coords.end(), [](double a, double b) {
            return compare_double(a, b) == 0;
        }), y_coords.end());

        // Create a map for quick index lookup of y-coordinates
        map<double, int> y_to_index;
        for (int i = 0; i < (int)y_coords.size(); ++i) {
            y_to_index[y_coords[i]] = i;
        }

        // 2. Sort x-events
        sort(events.begin(), events.end());

        // 3. Initialize Segment Tree
        // The segment tree operates on the n-1 elementary intervals defined by n unique y-coordinates.
        // The indices in the tree will range from 0 to y_coords.size() - 1.
        SegmentTree st(y_coords);

        double total_area = 0.0;
        double last_x = events[0].x;

        // 4. Sweep line
        for (const auto& event : events) {
            double current_x = event.x;

            // Calculate area of the strip between last_x and current_x
            double dx = current_x - last_x;
            if (compare_double(dx, 0.0) > 0) {
                // st.length[1] is the total length of the union of y-intervals
                total_area += st.length[1] * dx;
            }

            // Update the segment tree for the current event
            int y1_idx = y_to_index[event.y1];
            int y2_idx = y_to_index[event.y2];
            
            // The update range is [y1_idx, y2_idx). The segment tree is built on 
            // intervals [y_coords[i], y_coords[i+1]], which correspond to indices [i, i+1] in the tree.
            // The update function uses indices [start, end) where start and end are indices into y_coords.
            // The intervals to be covered are from y1_idx up to (but not including) y2_idx.
            // The segment tree is built on n unique y-coordinates, defining n-1 elementary intervals.
            // The indices for the intervals are 0 to n-2.
            // The update range should be [y1_idx, y2_idx) on the y_coords indices.
            st.update(1, 0, st.n - 1, y1_idx, y2_idx, event.type);

            last_x = current_x;
        }

        cout << total_area << "\n";
    }
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // Set precision for output
    cout << fixed << setprecision(2);

    solve();

    return 0;
}