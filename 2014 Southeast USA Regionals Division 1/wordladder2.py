import heapq
import sys

INF = 10**9

def word_dist(a, b, words):
    return sum(1 for i in range(len(words[a])) if words[a][i] != words[b][i])

def diffs(a, b, words):
    pos = [i for i in range(len(words[a])) if words[a][i] != words[b][i]]
    res1 = list(words[a])
    res2 = list(words[a])
    res1[pos[0]] = words[b][pos[0]]
    res2[pos[1]] = words[b][pos[1]]
    return [''.join(res1), ''.join(res2)]

def solve(pairs, words):
    res = ""
    for a, b in pairs:
        R = diffs(a, b, words)
        if not res:
            res = R[0]
        res = min(res, R[0], R[1])
    return res

def trace(dist, cur, D, N):
    res = []
    Q = [cur]
    while Q:
        cur = Q.pop(0)
        for i in range(N):
            d = D[i][cur]
            if d > 2:
                continue
            if d == 2 and dist[i][0] + d == dist[cur][1]:
                res.append((i, cur))
            if d == 1 and dist[i][1] + d == dist[cur][1]:
                Q.append(i)
    return res

def dijkstra(src, dest, words, D, N):
    dist = [[INF, INF] for _ in range(N)]
    heap = []
    
    dist[src][0] = 0
    heapq.heappush(heap, (0, 0, src))
    
    while heap:
        s, k, cur = heapq.heappop(heap)
        if s > dist[cur][k]:
            continue
            
        for nxt in range(N):
            d = D[cur][nxt]
            nk = 1 if d == 2 else 0
            if d > 2 or (nk == 1 and k == 1):
                continue
            if k == 1:
                nk = 1
                
            if s + d < dist[nxt][nk]:
                dist[nxt][nk] = s + d
                heapq.heappush(heap, (s + d, nk, nxt))
    
    if dist[dest][0] <= dist[dest][1]:
        return dist[dest][0], []
    
    pairs = trace(dist, dest, D, N)
    return dist[dest][1], pairs

def main():
    data = sys.stdin.read().splitlines()
    if not data:
        return
    
    N = int(data[0])
    words = [line.strip() for line in data[1:1+N]]
    
    D = [[INF] * N for _ in range(N)]
    for i in range(N):
        for j in range(i+1, N):
            dist = word_dist(i, j, words)
            D[i][j] = D[j][i] = dist
    
    steps, pairs = dijkstra(0, 1, words, D, N)
    
    if steps == INF or not pairs:
        print(0)
    else:
        print(solve(pairs, words))
    print(-1 if steps == INF else steps)

if __name__ == "__main__":
    main()