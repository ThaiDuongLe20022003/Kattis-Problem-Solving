def main():
    import sys
    n = int(sys.stdin.readline())
    
    fences = []
    l = list(range(n))
    r = list(range(n))
    
    for i in range(n):
        pos, strength = map(int, sys.stdin.readline().split())
        fences.append((pos, strength, i))
    
    fences.sort()
    
    change = True
    while change:
        change = False
        
        # Forward pass
        stack = []
        for i in range(n):
            while stack and abs(fences[i][0] - fences[stack[-1]][0]) <= fences[i][1]:
                j = stack.pop()
                if l[i] > l[j]:
                    l[i] = l[j]
                    change = True
                if r[i] < r[j]:
                    r[i] = r[j]
                    change = True
            stack.append(i)
        
        # Backward pass
        stack = []
        for i in range(n-1, -1, -1):
            while stack and abs(fences[i][0] - fences[stack[-1]][0]) <= fences[i][1]:
                j = stack.pop()
                if l[i] > l[j]:
                    l[i] = l[j]
                    change = True
                if r[i] < r[j]:
                    r[i] = r[j]
                    change = True
            stack.append(i)
    
    cans = [0] * n
    for i in range(n):
        original_idx = fences[i][2]
        cans[original_idx] = r[i] - l[i] + 1
    
    print(' '.join(map(str, cans)))

if __name__ == "__main__":
    main()