from collections import deque

def solve(r, c, initial_cells):
    """
    Solve the conquest campaign problem.
    
    Args:
        r: number of rows
        c: number of columns
        initial_cells: list of (row, col) tuples for initially occupied cells
    
    Returns:
        Number of days to conquer the entire grid
    """
    # Distance array: -1 means unvisited
    distance = [[-1] * c for _ in range(r)]
    
    # Initialize queue with all starting cells (day 1)
    queue = deque()
    for row, col in initial_cells:
        # Convert to 0-indexed
        row -= 1
        col -= 1
        if distance[row][col] == -1:  # Avoid duplicates
            distance[row][col] = 1
            queue.append((row, col))
    
    # BFS
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]  # right, left, down, up
    max_distance = 1
    
    while queue:
        row, col = queue.popleft()
        current_dist = distance[row][col]
        
        # Explore neighbors
        for dr, dc in directions:
            nr, nc = row + dr, col + dc
            
            # Check bounds and if unvisited
            if 0 <= nr < r and 0 <= nc < c and distance[nr][nc] == -1:
                distance[nr][nc] = current_dist + 1
                max_distance = max(max_distance, distance[nr][nc])
                queue.append((nr, nc))
    
    return max_distance

def main():
    # Read input
    r, c, n = map(int, input().split())
    initial_cells = []
    for _ in range(n):
        x, y = map(int, input().split())
        initial_cells.append((x, y))
    
    # Solve and print answer
    answer = solve(r, c, initial_cells)
    print(answer)

if __name__ == "__main__":
    main()