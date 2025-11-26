from collections import deque, defaultdict

def main():
    n = int(input())
    adj = defaultdict(set)
    
    for _ in range(n):
        line = input().split()
        if not line:
            continue
            
        first = line[0]
        for neighbor in line[1:]:
            adj[first].add(neighbor)
            adj[neighbor].add(first)
    
    start, end = input().split()
    
    prev = {}
    prev[start] = "thisisthestart"
    
    q = deque([start])
    while q:
        curr = q.popleft()
        
        for next_node in adj.get(curr, []):
            if next_node not in prev:
                prev[next_node] = curr
                q.append(next_node)
    
    if end not in prev:
        print("no route found")
        return
    
    ans = []
    current = end
    while current != "thisisthestart":
        ans.append(current)
        current = prev[current]
    
    ans.reverse()
    print(' '.join(ans))

if __name__ == "__main__":
    main()