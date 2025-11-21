def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    n = int(data[0])
    idx = 1
    
    junctions = []
    for _ in range(n - 1):
        u = int(data[idx]); v = int(data[idx + 1])
        idx += 2
        if u > v:
            u, v = v, u
        junctions.append((u, v))
    
    junctions = sorted(set(junctions))
    
    count = [0] * (n + 1)
    for u, v in junctions:
        count[u] += 1
        count[v] += 1
    
    connected = [[] for _ in range(n + 1)]
    for u, v in junctions:
        if count[u] != count[v]:
            if count[u] > count[v]:
                connected[u].append(v)
            else:
                connected[v].append(u)
        else:
            if u < v:
                connected[u].append(v)
            else:
                connected[v].append(u)
    
    visited = [0] * (n + 1)
    total = 0
    optimal = 0
    
    for i in range(1, n + 1):
        if count[i] > 0:
            total += count[i] * (count[i] - 1)
        for j in connected[i]:
            visited[j] = i
        for j in connected[i]:
            for k in connected[j]:
                if visited[k] == i:
                    optimal += 1
    
    print(total - 6 * optimal)

if __name__ == "__main__":
    main()