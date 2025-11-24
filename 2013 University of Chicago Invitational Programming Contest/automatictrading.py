import math
from typing import List

class SparseTable:
    def __init__(self, arr: List[int]):
        n = len(arr)
        self.logTwo = [0] * (n + 1)
        for i in range(2, n + 1):
            self.logTwo[i] = 1 + self.logTwo[i // 2]
        
        self.maxPow = self.logTwo[n] + 1
        self.memo = [[0] * n for _ in range(self.maxPow)]
        
        for j in range(self.maxPow):
            for i in range(n):
                if i + (1 << j) - 1 < n:
                    if j == 0:
                        self.memo[j][i] = arr[i]
                    else:
                        self.memo[j][i] = min(self.memo[j-1][i], self.memo[j-1][i + (1 << (j-1))])
    
    def query(self, l: int, r: int) -> int:
        if l > r:
            return 0
        j = self.logTwo[r - l + 1]
        return min(self.memo[j][l], self.memo[j][r - (1 << j) + 1])

class SuffixArray:
    def __init__(self, s: str):
        self.s = s
        self.N = len(s)
        self.sa = [0] * self.N
        self.pos = [0] * self.N
        self.lcp = [0] * self.N
        self.tmp = [0] * self.N
        self.gap = 0
    
    def sufCmp(self, i: int, j: int) -> bool:
        if self.pos[i] != self.pos[j]:
            return self.pos[i] < self.pos[j]
        i += self.gap
        j += self.gap
        return (i < self.N and j < self.N) and self.pos[i] < self.pos[j] or i > j
    
    def buildSA(self):
        for i in range(self.N):
            self.sa[i] = i
            self.pos[i] = ord(self.s[i])
        
        gap = 1
        while True:
            self.gap = gap
            self.sa.sort(key=lambda x: (self.pos[x], self.pos[x + gap] if x + gap < self.N else -1))
            self.tmp[0] = 0
            for i in range(self.N - 1):
                self.tmp[i + 1] = self.tmp[i] + (1 if self.sufCmp(self.sa[i], self.sa[i + 1]) else 0)
            for i in range(self.N):
                self.pos[self.sa[i]] = self.tmp[i]
            if self.tmp[self.N - 1] == self.N - 1:
                break
            gap *= 2
    
    def buildLCP(self):
        k = 0
        for i in range(self.N):
            if self.pos[i] != 0:
                j = self.sa[self.pos[i] - 1]
                while (i + k < self.N and j + k < self.N and 
                       self.s[i + k] == self.s[j + k]):
                    k += 1
                self.lcp[self.pos[i]] = k
                if k > 0:
                    k -= 1

def main():
    s = input().strip()
    sa = SuffixArray(s)
    sa.buildSA()
    
    inv = [0] * len(s)
    for i in range(len(s)):
        inv[sa.sa[i]] = i
    
    sa.buildLCP()
    
    temp = sa.lcp[:]
    st = SparseTable(temp)
    
    q = int(input())
    for _ in range(q):
        pos1, pos2 = map(int, input().split())
        p1 = inv[pos1]
        p2 = inv[pos2]
        if p1 > p2:
            p1, p2 = p2, p1
        print(st.query(p1 + 1, p2))

if __name__ == "__main__":
    main()