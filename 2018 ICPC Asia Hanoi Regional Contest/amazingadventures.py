from collections import deque, defaultdict

INF = float('inf')

class Edge:
    def __init__(self, to, cap, cost, rev):
        self.to = to
        self.cap = cap
        self.cost = cost
        self.rev = rev

class MinCostFlow:
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(n)]
    
    def add_edge(self, fr, to, cap, cost):
        self.graph[fr].append(Edge(to, cap, cost, len(self.graph[to])))
        self.graph[to].append(Edge(fr, 0, -cost, len(self.graph[fr]) - 1))
    
    def min_cost_flow(self, s, t, max_flow):
        res_cost = 0
        res_flow = 0
        
        while res_flow < max_flow:
            # SPFA (Shortest Path Faster Algorithm)
            dist = [INF] * self.n
            parent = [-1] * self.n
            parent_edge = [-1] * self.n
            in_queue = [False] * self.n
            
            dist[s] = 0
            queue = deque([s])
            in_queue[s] = True
            
            while queue:
                v = queue.popleft()
                in_queue[v] = False
                
                for i, edge in enumerate(self.graph[v]):
                    if edge.cap > 0 and dist[v] + edge.cost < dist[edge.to]:
                        dist[edge.to] = dist[v] + edge.cost
                        parent[edge.to] = v
                        parent_edge[edge.to] = i
                        
                        if not in_queue[edge.to]:
                            queue.append(edge.to)
                            in_queue[edge.to] = True
            
            if dist[t] == INF:
                break
            
            # Find bottleneck
            add_flow = max_flow - res_flow
            v = t
            while v != s:
                p = parent[v]
                edge_idx = parent_edge[v]
                add_flow = min(add_flow, self.graph[p][edge_idx].cap)
                v = p
            
            # Update flow
            v = t
            while v != s:
                p = parent[v]
                edge_idx = parent_edge[v]
                edge = self.graph[p][edge_idx]
                edge.cap -= add_flow
                self.graph[v][edge.rev].cap += add_flow
                res_cost += edge.cost * add_flow
                v = p
            
            res_flow += add_flow
        
        return res_flow, res_cost

def to_node(m, i, j, layer):
    """Convert (i, j, layer) to node index"""
    return ((m * i + j) << 1) + layer

def solve(n, m, start, mid, end, avoid):
    """Solve using min-cost max-flow"""
    # Total nodes: n*m*2 (each cell has 2 layers) + 2 (source and sink)
    total_nodes = n * m * 2 + 2
    s = total_nodes - 1  # source
    t = total_nodes - 2  # sink
    
    flow = MinCostFlow(total_nodes)
    
    # Build graph
    for i in range(n):
        for j in range(m):
            if (i, j) == avoid:
                continue
            
            # Self-loop: in -> out (capacity 1, cost 0)
            flow.add_edge(to_node(m, i, j, 0), to_node(m, i, j, 1), 1, 0)
            
            # Source connections
            if (i, j) == start:
                flow.add_edge(s, to_node(m, i, j, 0), 1, 0)
            if (i, j) == end:
                flow.add_edge(s, to_node(m, i, j, 0), 1, 0)
            
            # Sink connection (capacity 2 for mid)
            if (i, j) == mid:
                flow.add_edge(to_node(m, i, j, 0), t, 2, 0)
            
            # Movement edges to neighbors
            for di, dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
                ni, nj = i + di, j + dj
                if 0 <= ni < n and 0 <= nj < m and (ni, nj) != avoid:
                    flow.add_edge(to_node(m, i, j, 1), to_node(m, ni, nj, 0), 1, 1)
    
    # Find min-cost max-flow
    max_flow, min_cost = flow.min_cost_flow(s, t, 2)
    
    if max_flow != 2:
        return None
    
    # Reconstruct path
    directions = [[None] * m for _ in range(n)]
    
    for i in range(n):
        for j in range(m):
            if (i, j) == avoid:
                continue
            
            node_out = to_node(m, i, j, 1)
            for edge in flow.graph[node_out]:
                # Check if this edge was used in the flow
                if edge.cost == 1 and edge.cap == 0:  # capacity was 1, now 0 (fully used)
                    # Decode destination
                    dest_node = edge.to >> 1
                    ni = dest_node // m
                    nj = dest_node % m
                    
                    # Determine direction
                    if ni > i:
                        directions[i][j] = 'U'
                    elif ni < i:
                        directions[i][j] = 'D'
                    elif nj > j:
                        directions[i][j] = 'R'
                    elif nj < j:
                        directions[i][j] = 'L'
    
    # Follow path from start
    path1 = []
    i, j = start
    while directions[i][j] is not None:
        d = directions[i][j]
        path1.append(d)
        if d == 'U':
            i += 1
        elif d == 'D':
            i -= 1
        elif d == 'R':
            j += 1
        elif d == 'L':
            j -= 1
        if (i, j) == mid:
            break
    
    # Follow path from end and reverse
    path2 = []
    i, j = end
    while directions[i][j] is not None:
        d = directions[i][j]
        path2.append(d)
        if d == 'U':
            i += 1
        elif d == 'D':
            i -= 1
        elif d == 'R':
            j += 1
        elif d == 'L':
            j -= 1
        if (i, j) == mid:
            break
    
    # Reverse path2
    path2.reverse()
    reverse_map = {'U': 'D', 'D': 'U', 'L': 'R', 'R': 'L'}
    path2 = [reverse_map[d] for d in path2]
    
    return ''.join(path1 + path2)

def main():
    while True:
        line = input().strip()
        if not line:
            continue
        
        n, m = map(int, line.split())
        if n == 0 and m == 0:
            break
        
        rb, cb = map(int, input().split())
        rc, cc = map(int, input().split())
        rg, cg = map(int, input().split())
        ru, cu = map(int, input().split())
        
        try:
            input()  # blank line
        except:
            pass
        
        # Convert to 0-indexed
        start = (rb - 1, cb - 1)
        mid = (rc - 1, cc - 1)
        end = (rg - 1, cg - 1)
        avoid = (ru - 1, cu - 1)
        
        result = solve(n, m, start, mid, end, avoid)
        
        if result is None:
            print("NO")
        else:
            print("YES")
            print(result)

if __name__ == "__main__":
    main()