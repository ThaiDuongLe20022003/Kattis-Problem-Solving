def main():
    # Precompute win states
    win = [[False] * 501 for _ in range(501)]
    
    for i in range(1, 501):
        for j in range(1, 501):
            for k in range(1, j):
                if not win[k][i] and not win[j - k][i]:
                    win[i][j] = True
                    break

    n = int(input())
    
    for _ in range(n):
        b, d, s = input().split()
        b = int(b)
        d = int(d)
        
        print(s, end=' ')
        if s[0] == 'H':
            print("can win" if win[b][d] else "cannot win")
        else:
            print("can win" if win[d][b] else "cannot win")

if __name__ == "__main__":
    main()