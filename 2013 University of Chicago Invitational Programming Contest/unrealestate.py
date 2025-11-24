import sys
from math import fabs

# Set recursion limit higher for deep segment tree operations
sys.setrecursionlimit(200000)

# Constants for floating point comparison
EPS = 1e-9

# Custom comparison function for doubles
def compare_double(x, y):
    if fabs(x - y) < EPS:
        return 0
    return -1 if x < y else 1

# Segment Tree Implementation
class SegmentTree:
    def __init__(self, y_unique):
        self.y_coords = y_unique
        self.n = len(y_unique)
        # The tree will have nodes for n-1 elementary intervals
        # A safe size for a segment tree on n-1 leaves is 4 * n
        self.count = [0] * (4 * self.n)
        self.length = [0.0] * (4 * self.n)

    # Helper to update the length of a node
    def _update_length(self, node, start, end):
        if self.count[node] > 0:
            # If count > 0, the entire segment [y_coords[start], y_coords[end]] is covered
            self.length[node] = self.y_coords[end] - self.y_coords[start]
        elif start + 1 < end:
            # If count == 0 and it's not a leaf, sum up children's lengths
            self.length[node] = self.length[2 * node] + self.length[2 * node + 1]
        else:
            # If count == 0 and it's a leaf, length is 0
            self.length[node] = 0.0

    # Update the segment tree for a given y-interval [y1_idx, y2_idx)
    def update(self, node, start, end, y1_idx, y2_idx, delta):
        # [start, end] is the index range of y_coords for the current node
        # [y1_idx, y2_idx] is the index range of y_coords for the update interval

        # No overlap
        if start >= y2_idx or end <= y1_idx:
            return

        # Full overlap
        if start >= y1_idx and end <= y2_idx:
            self.count[node] += delta
            self._update_length(node, start, end)
            return

        # Partial overlap, recurse
        mid = start + (end - start) // 2
        self.update(2 * node, start, mid, y1_idx, y2_idx, delta)
        self.update(2 * node + 1, mid, end, y1_idx, y2_idx, delta)

        # After recursion, update the current node's length
        self._update_length(node, start, end)

    @property
    def total_covered_length(self):
        return self.length[1]

# Event structure for the sweep line
class Event:
    def __init__(self, x, y1, y2, type):
        self.x = x
        self.y1 = y1
        self.y2 = y2
        self.type = type # +1 for start of rectangle, -1 for end

    def __lt__(self, other):
        cmp_x = compare_double(self.x, other.x)
        if cmp_x != 0:
            return cmp_x < 0
        # Tie-breaking: process start events before end events (type +1 before -1)
        return self.type > other.type

def solve():
    input_data = sys.stdin.read().split()
    data_idx = 0
    
    while data_idx < len(input_data):
        try:
            n = int(input_data[data_idx])
            data_idx += 1
        except ValueError:
            # Handle case where the last line might be empty or non-numeric
            break

        if n == 0:
            break

        events = []
        y_coords = []

        for i in range(n):
            if data_idx + 4 > len(input_data):
                # Not enough data for a full rectangle, break
                break
                
            x1 = float(input_data[data_idx])
            y1 = float(input_data[data_idx+1])
            x2 = float(input_data[data_idx+2])
            y2 = float(input_data[data_idx+3])
            data_idx += 4

            # Ensure x1 < x2 and y1 < y2
            if compare_double(x1, x2) > 0: x1, x2 = x2, x1
            if compare_double(y1, y2) > 0: y1, y2 = y2, y1

            # Ignore zero-area rectangles
            if compare_double(x1, x2) == 0 or compare_double(y1, y2) == 0: continue

            # Start event
            events.append(Event(x1, y1, y2, 1))
            # End event
            events.append(Event(x2, y1, y2, -1))

            y_coords.append(y1)
            y_coords.append(y2)

        if not events:
            print(f"{0.0:.2f}")
            continue

        # 1. Sort and unique y-coordinates
        y_coords.sort(key=lambda y: y)
        
        y_unique = []
        if y_coords:
            y_unique.append(y_coords[0])
            for i in range(1, len(y_coords)):
                if compare_double(y_coords[i], y_coords[i-1]) != 0:
                    y_unique.append(y_coords[i])

        # Create a map for quick index lookup of y-coordinates
        y_to_index = {y: i for i, y in enumerate(y_unique)}

        # 2. Sort x-events
        events.sort()

        # 3. Initialize Segment Tree
        st = SegmentTree(y_unique)

        total_area = 0.0
        last_x = events[0].x

        # 4. Sweep line
        for event in events:
            current_x = event.x

            # Calculate area of the strip between last_x and current_x
            dx = current_x - last_x
            if compare_double(dx, 0.0) > 0:
                # st.total_covered_length is the total length of the union of y-intervals
                total_area += st.total_covered_length * dx

            # Update the segment tree for the current event
            y1_idx = y_to_index[event.y1]
            y2_idx = y_to_index[event.y2]
            
            # The update range is [y1_idx, y2_idx) on the y_unique indices.
            # The segment tree is built on n unique y-coordinates, defining n-1 elementary intervals.
            # The indices for the intervals are 0 to n-2.
            st.update(1, 0, st.n - 1, y1_idx, y2_idx, event.type)

            last_x = current_x

        print(f"{total_area:.2f}")

if __name__ == "__main__":
    solve()