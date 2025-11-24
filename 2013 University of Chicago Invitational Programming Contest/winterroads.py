import sys
from collections import deque, defaultdict

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
            return True
        return False

def main():
    data = sys.stdin.read().split()
    idx = 0
    
    n = int(data[idx]); idx += 1
    m = int(data[idx]); idx += 1
    
    adj = defaultdict(list)
    all_edges = [None] * (m + 1)
    capacities = [0] * (m + 1)
    
    initial_edges = []
    for i in range(1, m + 1):
        u = int(data[idx]); idx += 1
        v = int(data[idx]); idx += 1
        cap = int(data[idx]); idx += 1
        all_edges[i] = (u, v, i, cap)
        capacities[i] = cap
        initial_edges.append(all_edges[i])
    
    # Build initial MSF
    initial_edges.sort(key=lambda x: -x[3])
    dsu = DSU(n)
    
    for u, v, r_id, cap in initial_edges:
        if dsu.unite(u, v):
            adj[u].append((v, r_id))
            adj[v].append((u, r_id))
    
    e = int(data[idx]); idx += 1
    
    def check_path(a, b, w):
        visited = [False] * (n + 1)
        queue = deque([a])
        visited[a] = True
        
        while queue:
            u = queue.popleft()
            if u == b:
                return True
            for v, r_id in adj[u]:
                if not visited[v] and capacities[r_id] >= w:
                    visited[v] = True
                    queue.append(v)
        return False
    
    def remove_from_adj(u, v, r_id):
        adj[u] = [(neighbor, rid) for neighbor, rid in adj[u] if not (neighbor == v and rid == r_id)]
        adj[v] = [(neighbor, rid) for neighbor, rid in adj[v] if not (neighbor == u and rid == r_id)]
    
    def find_path_bottleneck(start, end):
        visited = [False] * (n + 1)
        parent = [0] * (n + 1)
        road_to_parent = [0] * (n + 1)
        queue = deque([start])
        visited[start] = True
        found = False
        
        while queue and not found:
            u = queue.popleft()
            for v, r_id in adj[u]:
                if not visited[v]:
                    visited[v] = True
                    parent[v] = u
                    road_to_parent[v] = r_id
                    queue.append(v)
                    if v == end:
                        found = True
                        break
        
        if not found:
            return (-1, -1)
        
        min_cap = float('inf')
        min_road_id = -1
        curr = end
        
        while curr != start:
            r_id = road_to_parent[curr]
            if capacities[r_id] < min_cap:
                min_cap = capacities[r_id]
                min_road_id = r_id
            curr = parent[curr]
        
        return (min_cap, min_road_id)
    
    def add_edge(u, v, r_id):
        adj[u].append((v, r_id))
        adj[v].append((u, r_id))
    
    for _ in range(e):
        type_char = data[idx]; idx += 1
        if type_char == 'S':
            a = int(data[idx]); idx += 1
            b = int(data[idx]); idx += 1
            w = int(data[idx]); idx += 1
            print(1 if check_path(a, b, w) else 0)
        else:
            r_id = int(data[idx]); idx += 1
            c_new = int(data[idx]); idx += 1
            c_old = capacities[r_id]
            capacities[r_id] = c_new
            u, v, _, _ = all_edges[r_id]
            
            was_in_msf = any(neighbor == v and rid == r_id for neighbor, rid in adj[u])
            
            if was_in_msf and c_new < c_old:
                remove_from_adj(u, v, r_id)
                
                # Find component containing u
                in_T_u = [False] * (n + 1)
                queue = deque([u])
                in_T_u[u] = True
                
                while queue:
                    curr = queue.popleft()
                    for neighbor, _ in adj[curr]:
                        if not in_T_u[neighbor]:
                            in_T_u[neighbor] = True
                            queue.append(neighbor)
                
                # Find best replacement edge
                max_cap = -1
                best_r_id = -1
                for j in range(1, m + 1):
                    uj, vj, _, cap_j = all_edges[j]
                    if in_T_u[uj] != in_T_u[vj]:
                        if capacities[j] > max_cap:
                            max_cap = capacities[j]
                            best_r_id = j
                
                if best_r_id != -1:
                    add_edge(all_edges[best_r_id][0], all_edges[best_r_id][1], best_r_id)
            
            elif not was_in_msf and c_new > c_old:
                min_cap, min_road_id = find_path_bottleneck(u, v)
                if min_cap != -1 and c_new > min_cap:
                    remove_from_adj(all_edges[min_road_id][0], all_edges[min_road_id][1], min_road_id)
                    add_edge(u, v, r_id)

if __name__ == "__main__":
    main()