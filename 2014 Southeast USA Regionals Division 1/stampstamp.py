import sys
from math import gcd
from functools import cmp_to_key

# Set recursion limit higher for potential deep recursion in convex hull
sys.setrecursionlimit(2000)

# Fast input reading
def input():
    return sys.stdin.readline().strip()

class Pt:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __lt__(self, other):
        if self.y != other.y:
            return self.y < other.y
        return self.x < other.x

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __hash__(self):
        return hash((self.x, self.y))

# Function to compute the cross product (orientation)
# > 0 for counter-clockwise, < 0 for clockwise, = 0 for collinear
def cross_product(a, b, c):
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x)

# Graham Scan for Convex Hull
def convex_hull(a):
    if len(a) <= 2:
        return a

    # 1. Find the point with the smallest y-coordinate (and smallest x in case of ties)
    p0 = min(a, key=lambda p: (p.y, p.x))

    # 2. Sort points by polar angle with respect to p0
    def polar_angle_cmp(p1, p2):
        cp = cross_product(p0, p1, p2)
        if cp != 0:
            return -1 if cp > 0 else 1 # Counter-clockwise order
        
        # Collinear case: sort by distance from p0
        dist1 = (p0.x - p1.x)**2 + (p0.y - p1.y)**2
        dist2 = (p0.x - p2.x)**2 + (p0.y - p2.y)**2
        return -1 if dist1 < dist2 else (1 if dist1 > dist2 else 0)

    a.sort(key=cmp_to_key(polar_angle_cmp))

    # 3. Build the hull
    st = []
    for p in a:
        while len(st) >= 2 and cross_product(st[-2], st[-1], p) <= 0:
            st.pop()
        st.append(p)

    return st

def solve():
    try:
        line = input().split()
    except EOFError:
        return
    
    if not line:
        return

    N = int(line[0]) # rows
    M = int(line[1]) # columns

    # Use a list of lists for the grid: grid[x][y]
    grid = [[False] * N for _ in range(M)]
    points = []
    number_of_points_total = 0

    # Read input and transform coordinates: (row, col) -> (x, y) where x=col, y=N-1-row
    for j in range(N):
        try:
            row = input()
        except EOFError:
            break
            
        for i in range(M):
            if row[i] == '#':
                grid[i][N - 1 - j] = True
                points.append(Pt(i, N - 1 - j))
                number_of_points_total += 1

    if number_of_points_total == 0:
        print(0)
        return
    if number_of_points_total <= 2:
        print(1)
        return

    # Calculate Convex Hull to reduce the number of points to check
    points = convex_hull(points)

    num_hull_points = len(points)
    if num_hull_points <= 2:
        print(1)
        return

    # Map to store the minimum GCD for each unique coprime direction vector (cx, cy)
    min_g_for_dir = {}
    # List to store the unique coprime direction vectors that appear twice
    seen_twice_dirs = []

    # Iterate over the edges of the convex hull
    for i in range(num_hull_points):
        p = points[i]
        q = points[(i + 1) % num_hull_points]

        # Calculate the direction vector (dx, dy)
        dx = q.x - p.x
        dy = q.y - p.y

        # Calculate GCD to find the coprime direction vector (cx, cy)
        common_divisor = gcd(abs(dx), abs(dy))
        g = common_divisor
        
        # Normalize the direction vector to coprime (cx, cy)
        cx = dx // g
        cy = dy // g

        # Ensure the coprime vector is canonical (e.g., first non-zero component is positive)
        if cx < 0 or (cx == 0 and cy < 0):
            cx = -cx
            cy = -cy
        
        cpair = (cx, cy)

        if cpair in min_g_for_dir:
            # If seen before, this is the second (or more) time.
            # Update the minimum g (which corresponds to the maximum shift k)
            if min_g_for_dir[cpair] == -1:
                # First time seeing the second instance
                seen_twice_dirs.append(cpair)
                min_g_for_dir[cpair] = g
            else:
                min_g_for_dir[cpair] = min(min_g_for_dir[cpair], g)
        else:
            # First time seeing this direction
            min_g_for_dir[cpair] = -1 # Use -1 as a sentinel for "seen once"

    best_score = number_of_points_total # Initialize with the worst case

    # Iterate over all possible relative shifts (dx, dy)
    for cpair in seen_twice_dirs:
        cx, cy = cpair
        max_k = min_g_for_dir[cpair]

        for k in range(1, max_k + 1):
            dx = k * cx
            dy = k * cy
            current_score = 0
            is_valid = True
            
            # Iterate over all cells (x, y) in the grid
            for x in range(M):
                for y in range(N):
                    # Check if (x, y) is the start of a run
                    is_marked = grid[x][y]
                    
                    # Check the cell before: (x - dx, y - dy)
                    prev_x = x - dx
                    prev_y = y - dy
                    prev_is_marked = False
                    if 0 <= prev_x < M and 0 <= prev_y < N:
                        prev_is_marked = grid[prev_x][prev_y]
                    
                    if is_marked and not prev_is_marked:
                        # This is the start of a run. Calculate the run length.
                        run_length = 0
                        cur_x = x
                        cur_y = y
                        
                        while 0 <= cur_x < M and 0 <= cur_y < N and grid[cur_x][cur_y]:
                            run_length += 1
                            cur_x += dx
                            cur_y += dy
                        
                        if run_length == 1:
                            is_valid = False
                            break
                        current_score += (run_length + 1) // 2
                
                if not is_valid:
                    break
            
            if is_valid:
                best_score = min(best_score, current_score)

    print(best_score)

if __name__ == "__main__":
    solve()