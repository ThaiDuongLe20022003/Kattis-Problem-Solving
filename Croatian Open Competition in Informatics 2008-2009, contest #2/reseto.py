def solve():
    N, K = map(int, input().split())
    crossed = [False] * (N + 1)
    cross_order = []

    for i in range(2, N + 1):
        if not crossed[i]:
            # cross out i itself
            if not crossed[i]:
                crossed[i] = True
                cross_order.append(i)
            # cross out multiples
            for j in range(i * 2, N + 1, i):
                if not crossed[j]:
                    crossed[j] = True
                    cross_order.append(j)
        if len(cross_order) >= K:
            break

    print(cross_order[K - 1])

if __name__ == "__main__":
    solve()