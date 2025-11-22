import heapq
import sys

def main():
    INF = float('inf')
    
    for line in sys.stdin:
        n = int(line.strip())
        if n == 0:
            break
            
        stones = []
        unique_widths_set = set()
        
        for _ in range(n):
            a, b, h = map(int, sys.stdin.readline().split())
            stones.append((a, b, h))
            unique_widths_set.add(a)
            unique_widths_set.add(b)
            
        start_width, end_width = map(int, sys.stdin.readline().split())
        unique_widths_set.add(start_width)
        unique_widths_set.add(end_width)
        
        # Map widths to node IDs
        width_to_id = {}
        id_to_width = []
        for i, width in enumerate(sorted(unique_widths_set)):
            width_to_id[width] = i
            id_to_width.append(width)
        num_nodes = len(unique_widths_set)
        
        # Build graph
        adj = [[] for _ in range(num_nodes)]
        for a, b, h in stones:
            cost = (a + b) * h
            u = width_to_id[a]
            v = width_to_id[b]
            adj[u].append((v, cost))
            adj[v].append((u, cost))
            
        # Dijkstra's algorithm
        start_node = width_to_id[start_width]
        end_node = width_to_id[end_width]
        dist = [INF] * num_nodes
        dist[start_node] = 0
        
        pq = [(0.0, start_node)]
        
        while pq:
            d, u = heapq.heappop(pq)
            if d > dist[u]:
                continue
            if u == end_node:
                break
                
            for v, weight in adj[u]:
                new_dist = dist[u] + weight
                if new_dist < dist[v]:
                    dist[v] = new_dist
                    heapq.heappush(pq, (new_dist, v))
                    
        min_cost_dollars = dist[end_node] / 100.0
        print(f"{min_cost_dollars:.2f}")

if __name__ == "__main__":
    main()