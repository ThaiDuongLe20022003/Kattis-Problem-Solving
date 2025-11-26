class UnionFind:
    def __init__(self, n):
        self.p = list(range(n))
        self.rank = [0] * n
        self.set_size = [1] * n
        self.num_sets = n
    
    def find_set(self, i):
        if self.p[i] == i:
            return i
        self.p[i] = self.find_set(self.p[i])
        return self.p[i]
    
    def is_same_set(self, i, j):
        return self.find_set(i) == self.find_set(j)
    
    def union_set(self, i, j):
        if not self.is_same_set(i, j):
            self.num_sets -= 1
            x = self.find_set(i)
            y = self.find_set(j)
            
            if self.rank[x] > self.rank[y]:
                self.p[y] = x
                self.set_size[x] += self.set_size[y]
            else:
                self.p[x] = y
                self.set_size[y] += self.set_size[x]
                if self.rank[x] == self.rank[y]:
                    self.rank[y] += 1

def main():
    n = int(input())
    rads = []
    coords = []
    
    for _ in range(n):
        x, y, r = map(int, input().split())
        rads.append(r)
        coords.append((x, y))
    
    uf = UnionFind(n + 2)
    idx = 0
    
    while idx < n:
        # Check left wall collision
        if coords[idx][0] - rads[idx] < 0:
            uf.union_set(0, idx + 2)
        # Check right wall collision
        if coords[idx][0] + rads[idx] > 200:
            uf.union_set(1, idx + 2)
        
        # Check intersection with previous circles
        for j in range(idx):
            dx = coords[idx][0] - coords[j][0]
            dy = coords[idx][1] - coords[j][1]
            r_sum = rads[idx] + rads[j]
            
            if dx * dx + dy * dy < r_sum * r_sum:
                uf.union_set(idx + 2, j + 2)
        
        # Check if left and right walls are connected
        if uf.is_same_set(0, 1):
            break
            
        idx += 1
    
    print(idx)

if __name__ == "__main__":
    main()