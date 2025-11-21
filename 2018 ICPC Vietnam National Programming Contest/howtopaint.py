MOD = 100003
MAXN = 1005

def main():
    import sys
    data = sys.stdin.read().split()
    
    m = int(data[0])
    n = int(data[1])
    assert 0 < m <= 1000
    assert 0 < n <= 1000
    
    a = list(map(int, data[2:2+m]))
    b = [n - x for x in a]
    
    p = sum(a)
    q = sum(b)
    
    b.sort(reverse=True)
    
    numerator = 1
    denominator = 1
    base = 0
    
    def update_hook(w):
        nonlocal denominator
        assert w[0] > 0
        for i in range(1, len(w)):
            assert w[i] <= w[i-1]
        
        filled = [[False] * MAXN for _ in range(MAXN)]
        ups = [[0] * MAXN for _ in range(MAXN)]
        rights = [[0] * MAXN for _ in range(MAXN)]
        
        for i in range(len(w)):
            for j in range(w[i]):
                filled[i][j] = True
        
        for i in range(m-1, -1, -1):
            for j in range(n-1, -1, -1):
                if filled[i][j]:
                    ups[i][j] = 1 + ups[i+1][j] if i+1 < m and filled[i+1][j] else 1
                    rights[i][j] = 1 + rights[i][j+1] if j+1 < n and filled[i][j+1] else 1
                    hook = ups[i][j] + rights[i][j] - 1
                    denominator = (denominator * hook) % MOD
    
    def multiply(x):
        nonlocal numerator, base
        while x % MOD == 0:
            base += 1
            x //= MOD
        numerator = (numerator * x) % MOD
    
    update_hook(a)
    update_hook(b)
    
    for i in range(1, p + q - 1):
        multiply(i)
    multiply(p)
    multiply(q)
    
    for i in range(MOD - 2):
        numerator = (numerator * denominator) % MOD
    
    print(f"{base} {numerator}")

if __name__ == "__main__":
    main()