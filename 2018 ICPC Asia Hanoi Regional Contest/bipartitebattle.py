MOD = 10**9 + 7

def solve(n, graphs):
    
    # Calculate total number of vertices
    total_vertices = sum(a + b for a, b in graphs)
    
    # Calculate total possible edges
    total_edges = sum(a * b for a, b in graphs)
    
    if total_vertices % 2 == 1:
        return 0
    else:
        result = pow(2, total_edges - 1, MOD)
        return result

def main():
    n = int(input())
    graphs = []
    for _ in range(n):
        a, b = map(int, input().split())
        graphs.append((a, b))
    
    answer = solve(n, graphs)
    print(answer)

if __name__ == "__main__":
    main()