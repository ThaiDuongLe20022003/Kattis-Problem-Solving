from collections import deque
import sys

class DSU:
    def __init__(self, n):
        self.parent = list(range(n + 1))
    
    def find(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]
    
    def unite(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            self.parent[root_i] = root_j

def main():
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    data = sys.stdin.read().splitlines()
    idx = 0
    map_num = 1
    first_map_output = True
    
    while idx < len(data):
        line = data[idx].strip()
        idx += 1
        
        # Skip empty lines
        while idx < len(data) and not line:
            line = data[idx].strip()
            idx += 1
        
        if not line:
            break
        
        if not first_map_output:
            print()
        first_map_output = False
        
        grid_lines = [line]
        while idx < len(data) and data[idx].strip():
            grid_lines.append(data[idx].strip())
            idx += 1
        
        R = len(grid_lines)
        C = len(grid_lines[0])
        
        grid = [list(line) for line in grid_lines]
        visited_island = [[False] * C for _ in range(R)]
        visited_bridge = [[False] * C for _ in range(R)]
        island_id_grid = [[0] * C for _ in range(R)]
        
        def is_valid(r, c):
            return 0 <= r < R and 0 <= c < C
        
        def bfs_island(r, c, id):
            queue = deque()
            queue.append((r, c))
            visited_island[r][c] = True
            island_id_grid[r][c] = id
            
            while queue:
                curr_r, curr_c = queue.popleft()
                
                for i in range(4):
                    nr = curr_r + dr[i]
                    nc = curr_c + dc[i]
                    
                    if is_valid(nr, nc) and not visited_island[nr][nc] and \
                       (grid[nr][nc] == '#' or grid[nr][nc] == 'X'):
                        visited_island[nr][nc] = True
                        island_id_grid[nr][nc] = id
                        queue.append((nr, nc))
        
        # 1. Identify Islands
        island_count = 0
        for r in range(R):
            for c in range(C):
                if not visited_island[r][c] and (grid[r][c] == '#' or grid[r][c] == 'X'):
                    island_count += 1
                    bfs_island(r, c, island_count)
        
        def bfs_find_islands_for_bridge(r, c):
            adjacent_island_ids = set()
            queue = deque()
            queue.append((r, c))
            visited_bridge[r][c] = True
            
            while queue:
                curr_r, curr_c = queue.popleft()
                
                for i in range(4):
                    nr = curr_r + dr[i]
                    nc = curr_c + dc[i]
                    
                    if is_valid(nr, nc):
                        if grid[nr][nc] == 'B' and not visited_bridge[nr][nc]:
                            visited_bridge[nr][nc] = True
                            queue.append((nr, nc))
                        elif grid[nr][nc] == 'X':
                            island_id = island_id_grid[nr][nc]
                            if island_id != 0:
                                adjacent_island_ids.add(island_id)
            return adjacent_island_ids
        
        # 2. Count Bridges & Connect Islands
        dsu = DSU(island_count)
        bridge_count = 0
        bus_count = island_count
        
        for r in range(R):
            for c in range(C):
                if grid[r][c] == 'B' and not visited_bridge[r][c]:
                    bridge_count += 1
                    connected_islands = bfs_find_islands_for_bridge(r, c)
                    
                    if len(connected_islands) == 2:
                        id1, id2 = list(connected_islands)
                        if dsu.find(id1) != dsu.find(id2):
                            dsu.unite(id1, id2)
                            bus_count -= 1
        
        print(f"Map {map_num}")
        print(f"islands: {island_count}")
        print(f"bridges: {bridge_count}")
        print(f"buses needed: {bus_count}")
        
        map_num += 1

if __name__ == "__main__":
    main()