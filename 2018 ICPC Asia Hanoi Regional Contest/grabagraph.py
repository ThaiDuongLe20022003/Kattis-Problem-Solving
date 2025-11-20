def main():
    # Pre-compute Fibonacci numbers
    fib = [0] * 87
    fib[0] = fib[1] = 1
    for i in range(2, 87):
        fib[i] = fib[i-1] + fib[i-2]
    
    # Pre-build base graphs
    bash_base = []
    for i in range(60):
        # Edge from vertex (i+3) to vertex 2 with weight (i+1)
        bash_base.append((i + 3, 2, i + 1))
        # Edges from vertex (i+3) to vertices (j+3) for j < i
        for j in range(i):
            bash_base.append((i + 3, j + 3, i - j))
    
    chikapu_base = []
    for i in range(3, 89):
        # Edge from vertex i to vertex (i-1) with weight 1
        chikapu_base.append((i, i - 1, 1))
        # Edge from vertex i to vertex (i-2) with weight 2 (if i > 3)
        if i > 3:
            chikapu_base.append((i, i - 2, 2))
    
    while True:
        try:
            a = int(input())
            if a == -1:
                break
            
            # Bash's graph
            bash_edges = bash_base[:]
            for i in range(60):
                if (a >> i) & 1:  # Check if bit i is set
                    bash_edges.append((1, i + 3, 60 - i))
            
            print("YES")
            print(62, len(bash_edges))
            for u, v, w in bash_edges:
                print(u, v, w)
            
            # Chikapu's graph (Zeckendorf decomposition)
            chikapu_edges = chikapu_base[:]
            remaining = a
            for i in range(86, -1, -1):
                if remaining >= fib[i]:
                    remaining -= fib[i]
                    chikapu_edges.append((1, i + 2, 87 - i))
            
            print("YES")
            print(88, len(chikapu_edges))
            for u, v, w in chikapu_edges:
                print(u, v, w)
        
        except EOFError:
            break

if __name__ == "__main__":
    main()