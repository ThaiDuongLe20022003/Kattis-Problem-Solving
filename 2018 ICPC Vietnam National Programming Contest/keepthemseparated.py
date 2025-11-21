MAX_N = 2503
MOD = 1000000782
MAX_Q = 100005
BASE = 102240

class Element:
    def __init__(self, x1=0, y1=0, x2=0, y2=0):
        self.x1 = x1
        self.y1 = y1
        self.x2 = x2
        self.y2 = y2

fw = [[0] * MAX_N for _ in range(MAX_N)]
power = [0] * MAX_Q
a = [Element() for _ in range(MAX_Q)]

def update_single(x, y, val):
    i = x
    while i < MAX_N:
        j = y
        while j < MAX_N:
            fw[i][j] = (fw[i][j] + val) % MOD
            j += j & -j
        i += i & -i

def update_range(x1, y1, x2, y2, val):
    update_single(x1, y1, val)
    update_single(x1, y2 + 1, MOD - val)
    update_single(x2 + 1, y1, MOD - val)
    update_single(x2 + 1, y2 + 1, val)

def get(x, y):
    sum_val = 0
    i = x
    while i > 0:
        j = y
        while j > 0:
            sum_val = (sum_val + fw[i][j]) % MOD
            j -= j & -j
        i -= i & -i
    return sum_val

def main():
    import sys
    data = sys.stdin.read().split()
    idx = 0
    
    power[0] = 1
    query = int(data[idx]); idx += 1
    
    for i in range(1, query + 1):
        power[i] = (power[i - 1] * BASE) % MOD
    
    for i in range(1, query + 1):
        type_val = int(data[idx]); idx += 1
        if type_val == 1:
            x1 = (int(data[idx]) + 1) // 2; idx += 1
            y1 = (int(data[idx]) + 1) // 2; idx += 1
            x2 = (int(data[idx]) - 1) // 2; idx += 1
            y2 = (int(data[idx]) - 1) // 2; idx += 1
            a[i] = Element(x1, y1, x2, y2)
            update_range(x1, y1, x2, y2, power[i])
        elif type_val == 2:
            p = int(data[idx]); idx += 1
            update_range(a[p].x1, a[p].y1, a[p].x2, a[p].y2, MOD - power[p])
        else:
            x1 = int(data[idx]) // 2; idx += 1
            y1 = int(data[idx]) // 2; idx += 1
            x2 = int(data[idx]) // 2; idx += 1
            y2 = int(data[idx]) // 2; idx += 1
            K2 = get(x2, y2)
            K1 = get(x1, y1)
            print('Y' if K1 == K2 else 'N', end='')

if __name__ == "__main__":
    main()