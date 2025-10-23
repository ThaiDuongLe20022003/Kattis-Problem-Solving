from math import sqrt
r = []

def cal():
    n,e = [int(c) for c in input().split(" ")]
    p = -1
    for i in range(2,int(sqrt(n))+1):
        if n % i == 0:
            p = i
            break
    q = n / p
    c = (p-1)*(q-1)
    j = 1
    while True:
        b = c*j
        if (b+1)%e == 0:
            return (b+1)/e
        j += 1

t = int(input())
for i in range(t):
    r.append(cal())
for i in r:
    print(int(i))