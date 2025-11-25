import sys

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Circle:
    def __init__(self, origin, radius, i):
        self.origin = origin
        self.radius = radius
        self.i = i
    
    def __lt__(self, other):
        if self.radius != other.radius:
            return self.radius < other.radius
        if self.origin.x != other.origin.x:
            return self.origin.x < other.origin.x
        return self.origin.y < other.origin.y
    
    def encloses(self, other):
        return (self.radius > other.radius and 
                squared_dist(self.origin, other.origin) < self.radius * self.radius)

def squared_dist(a, b):
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    
    n = int(data[0])
    idx = 1
    
    circles = []
    energy = [[0, 0] for _ in range(n + 1)]
    
    for i in range(1, n + 1):
        x = int(data[idx]); y = int(data[idx + 1]); r = int(data[idx + 2])
        a = int(data[idx + 3]); b = int(data[idx + 4])
        idx += 5
        
        circles.append(Circle(Point(x, y), r, i))
        energy[i] = [a, b]
    
    circles.sort()
    
    e = 0
    parent = [0] * (n + 1)
    depth = [0] * (n + 1)
    total = [0] * (n + 1)
    peak = [[0, 0] for _ in range(n + 1)]
    
    for i in range(n - 2, -1, -1):
        for j in range(i + 1, n):
            if circles[j].encloses(circles[i]):
                c1 = circles[i].i
                c2 = circles[j].i
                parent[c1] = c2
                depth[c1] = depth[c2] + 1
                
                for d in range(depth[c1] + 1):
                    if peak[c1][0] < total[c1]:
                        peak[c1][0] = total[c1]
                        peak[c1][1] = d
                    if d == depth[c1]:
                        break
                    total[c1] += energy[c1][d & 1]
                
                e += peak[c1][0]
                break
    
    print(e)
    
    affected = [False] * (n + 1)
    drawn = [False] * (n + 1)
    skip = [False] * (n + 1)
    
    for _ in range(n):
        j = -1
        for i in range(n):
            c = circles[i].i
            affected[c] = False
            if skip[c] or (depth[c] == peak[c][1] and not drawn[c]):
                if parent[c]:
                    skip[parent[c]] = True
            if skip[c]:
                continue
            if total[c] == peak[c][0] and not drawn[c] and (j == -1 or circles[j].i > c):
                j = i
        
        c1 = circles[j].i
        print(c1, end=" ")
        drawn[c1] = True
        affected[c1] = True
        
        for i in range(n - 1, -1, -1):
            c2 = circles[i].i
            skip[c2] = False
            if parent[c2] and affected[parent[c2]]:
                affected[c2] = True
                depth[c2] -= 1
                total[c2] -= energy[c2][depth[c2] & 1]
    
    print()

if __name__ == "__main__":
    main()