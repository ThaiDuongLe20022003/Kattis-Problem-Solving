MOD = 1000000007
INF = 1 << 60

def modinverse(a, b=MOD):
    return 1 if a == 1 else b - modinverse(b % a, a) * b // a

def clean(n):
    while n < MOD:
        n += MOD
    return n % MOD

def main():
    n = int(input().strip())
    
    memo = [[0] * (n + 1) for _ in range(n + 1)]
    
    print("1 1 1", flush=True)
    t1, t2 = map(int, input().split())
    memo[1][1] = t2
    
    ans = [t2]
    
    for i in range(2, n + 1):
        print(f"1 1 {i}", flush=True)
        t1, t2 = map(int, input().split())
        
        if t1 == 1:
            val = t2 - memo[i - 1][1]
            val = clean(val)
        elif t1 == i:
            val = t2 * modinverse(memo[i - 1][i - 1])
            val = clean(val)
        else:
            val = (t2 - memo[i - 1][t1])
            val = clean(val)
            val *= modinverse(memo[i - 1][t1 - 1])
            val = clean(val)
        
        for j in range(1, i + 1):
            if j == 1:
                memo[i][j] = memo[i - 1][j] + val
                memo[i][j] = clean(memo[i][j])
            elif j == i:
                memo[i][j] = memo[i - 1][j - 1] * val
                memo[i][j] = clean(memo[i][j])
            else:
                memo[i][j] = memo[i - 1][j] + memo[i - 1][j - 1] * val
                memo[i][j] = clean(memo[i][j])
        
        ans.append(val)
    
    print("2", *ans, flush=True)

if __name__ == "__main__":
    main()