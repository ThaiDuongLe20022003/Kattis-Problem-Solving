import collections
import sys

class Arc:
    def __init__(self, u, rev, cap):
        self.u = u
        self.rev = rev
        self.cap = cap
        self.initial_cap = cap

class FlowNetwork:
    def __init__(self, n):
        self.n = n
        self.network = [[] for _ in range(n)]
        self.dist = [-1] * n
        self.iter = [0] * n
    
    def add_arc(self, u, v, cap_uv, cap_vu=0):
        if u == v:
            return
        
        self.network[u].append(Arc(v, len(self.network[v]), cap_uv))
        self.network[v].append(Arc(u, len(self.network[u]) - 1, cap_vu))
    
    def bfs(self, s, t):
        self.dist = [-1] * self.n
        self.dist[s] = 0
        q = collections.deque([s])
        
        while q:
            v = q.popleft()
            for arc in self.network[v]:
                if arc.cap > 0 and self.dist[arc.u] == -1:
                    self.dist[arc.u] = self.dist[v] + 1
                    q.append(arc.u)
        
        return self.dist[t] != -1
    
    def dfs(self, v, t, flow):
        if v == t:
            return flow
        
        while self.iter[v] < len(self.network[v]):
            arc = self.network[v][self.iter[v]]
            if arc.cap > 0 and self.dist[arc.u] == self.dist[v] + 1:
                f = self.dfs(arc.u, t, min(flow, arc.cap))
                if f > 0:
                    arc.cap -= f
                    self.network[arc.u][arc.rev].cap += f
                    return f
            self.iter[v] += 1
        
        return 0
    
    def max_flow(self, s, t):
        flow = 0
        
        while self.bfs(s, t):
            self.iter = [0] * self.n
            while True:
                f = self.dfs(s, t, float('inf'))
                if f == 0:
                    break
                flow += f
        
        return flow

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    
    n = int(data[0])
    idx = 1
    
    fn = FlowNetwork(1002)
    s, t = 1000, 1001
    
    # Build the 3D grid network
    for i in range(10):
        for j in range(10):
            for k in range(10):
                u = i * 100 + j * 10 + k
                fn.add_arc(u, (i - 1) * 100 + j * 10 + k if i > 0 else t, 1)
                fn.add_arc(u, (i + 1) * 100 + j * 10 + k if i < 9 else t, 1)
                fn.add_arc(u, i * 100 + (j - 1) * 10 + k if j > 0 else t, 1)
                fn.add_arc(u, i * 100 + (j + 1) * 10 + k if j < 9 else t, 1)
                fn.add_arc(u, i * 100 + j * 10 + (k - 1) if k > 0 else t, 1)
                fn.add_arc(u, i * 100 + j * 10 + (k + 1) if k < 9 else t, 1)
    
    # Add source connections
    for _ in range(n):
        x, y, z = int(data[idx]), int(data[idx+1]), int(data[idx+2])
        idx += 3
        fn.add_arc(s, x * 100 + y * 10 + z, 6)
    
    result = fn.max_flow(s, t)
    print(result)

if __name__ == "__main__":
    main()