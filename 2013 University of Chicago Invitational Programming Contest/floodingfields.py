import sys
from collections import deque

class Edge:
    def __init__(self, a, b, cap, flow):
        self.a = a
        self.b = b
        self.cap = cap
        self.flow = flow

class MaxFlow:
    def __init__(self, n, s, t):
        self.n = n
        self.s = s
        self.t = t
        self.d = [0] * n
        self.ptr = [0] * n
        self.q = [0] * n
        self.e = []
        self.g = [[] for _ in range(n)]
        self.INF = 1 << 60
    
    def add_edge(self, a, b, cap):
        e1 = Edge(a, b, cap, 0)
        e2 = Edge(b, a, 0, 0)
        self.g[a].append(len(self.e))
        self.e.append(e1)
        self.g[b].append(len(self.e))
        self.e.append(e2)
    
    def bfs(self):
        qh, qt = 0, 0
        self.q[qt] = self.s
        qt += 1
        self.d = [-1] * self.n
        self.d[self.s] = 0
        
        while qh < qt and self.d[self.t] == -1:
            v = self.q[qh]
            qh += 1
            for id in self.g[v]:
                to = self.e[id].b
                if self.d[to] == -1 and self.e[id].flow < self.e[id].cap:
                    self.q[qt] = to
                    qt += 1
                    self.d[to] = self.d[v] + 1
        return self.d[self.t] != -1
    
    def dfs(self, v, flow):
        if flow == 0:
            return 0
        if v == self.t:
            return flow
        
        while self.ptr[v] < len(self.g[v]):
            id = self.g[v][self.ptr[v]]
            to = self.e[id].b
            if self.d[to] != self.d[v] + 1:
                self.ptr[v] += 1
                continue
            
            pushed = self.dfs(to, min(flow, self.e[id].cap - self.e[id].flow))
            if pushed > 0:
                self.e[id].flow += pushed
                self.e[id ^ 1].flow -= pushed
                return pushed
            
            self.ptr[v] += 1
        return 0
    
    def get_flow(self):
        flow = 0
        while self.bfs():
            self.ptr = [0] * self.n
            while True:
                pushed = self.dfs(self.s, self.INF)
                if pushed == 0:
                    break
                flow += pushed
        return flow

def in_range(r, c, n):
    return 0 <= r < n and 0 <= c < n

def get_node(r, c, t, in_node, n, h):
    return (((r * n + c) * h + t) * 2) + (1 if in_node else 0)

def main():
    data = sys.stdin.read().split()
    idx = 0
    
    n = int(data[idx]); idx += 1
    k = int(data[idx]); idx += 1
    h = int(data[idx]); idx += 1
    
    # Read grid
    grid = []
    for i in range(n):
        row = []
        for j in range(n):
            row.append(int(data[idx])); idx += 1
        grid.append(row)
    
    # Read cows
    cows = []
    for i in range(k):
        r = int(data[idx]); c = int(data[idx + 1]); idx += 2
        cows.append((r, c))
    
    # Read water levels
    water = []
    for i in range(h):
        water.append(int(data[idx])); idx += 1
    
    # Adjust water levels
    water_adj = [-1] + water
    h += 1
    
    # Create flow graph
    N = (n * n * h * 2) + 2
    S = N - 1
    T = N - 2
    mf = MaxFlow(N, S, T)
    
    # Source to each cow
    for r, c in cows:
        mf.add_edge(S, get_node(r, c, 0, True, n, h), 1)
    
    # Each node at last time to sink
    for i in range(n):
        for j in range(n):
            mf.add_edge(get_node(i, j, h - 1, False, n, h), T, 1)
    
    # Connect node to itself if not flooded
    for i in range(n):
        for j in range(n):
            for t in range(h):
                if grid[i][j] > water_adj[t]:
                    mf.add_edge(get_node(i, j, t, True, n, h), get_node(i, j, t, False, n, h), 1)
    
    # Directions: up, down, right, left, stay
    dx = [-1, 1, 0, 0, 0]
    dy = [0, 0, 1, -1, 0]
    
    # Connect in all 5 directions for each time
    for i in range(n):
        for j in range(n):
            for t in range(h - 1):
                for l in range(5):
                    ni = i + dx[l]
                    nj = j + dy[l]
                    if in_range(ni, nj, n):
                        mf.add_edge(get_node(i, j, t, False, n, h), get_node(ni, nj, t + 1, True, n, h), 1)
    
    print(mf.get_flow())

if __name__ == "__main__":
    main()