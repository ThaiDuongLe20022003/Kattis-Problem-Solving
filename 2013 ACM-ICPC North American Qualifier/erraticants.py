from collections import deque, defaultdict

def main():
    n = int(input().strip())
    input()  # Consume blank line
    
    for path_num in range(n):
        s = int(input().strip())
        
        adj = defaultdict(set)
        current_pos = (0, 0)
        start_node = (0, 0)
        
        for _ in range(s):
            dir_char = input().strip()
            
            x, y = current_pos
            if dir_char == 'N':
                next_pos = (x, y + 1)
            elif dir_char == 'E':
                next_pos = (x + 1, y)
            elif dir_char == 'S':
                next_pos = (x, y - 1)
            elif dir_char == 'W':
                next_pos = (x - 1, y)
            
            # Add bidirectional edges
            adj[current_pos].add(next_pos)
            adj[next_pos].add(current_pos)
            
            current_pos = next_pos
        
        food_location = current_pos
        
        # BFS
        dist = {}
        queue = deque()
        shortest_path = -1
        
        dist[start_node] = 0
        queue.append(start_node)
        
        while queue:
            u = queue.popleft()
            d = dist[u]
            
            if u == food_location:
                shortest_path = d
                break
            
            if u in adj:
                for v in adj[u]:
                    if v not in dist:
                        dist[v] = d + 1
                        queue.append(v)
        
        print(shortest_path)
        
        # Consume blank line if not last path
        if path_num < n - 1:
            input()

if __name__ == "__main__":
    main()