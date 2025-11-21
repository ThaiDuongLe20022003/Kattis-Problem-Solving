class Poke:
    def __init__(self, a, d, h):
        self.a = a
        self.d = d
        self.h = h
    
    def __lt__(self, other):
        return (self.a, self.d, self.h) < (other.a, other.d, other.h)
    
    def __eq__(self, other):
        return self.a == other.a and self.d == other.d and self.h == other.h
    
    def __hash__(self):
        return hash((self.a, self.d, self.h))

def main():
    n, m = map(int, input().split())
    
    v = []
    for _ in range(n):
        a, d, h = map(int, input().split())
        v.append(Poke(a, d, h))
    
    all_set = set()
    
    v.sort(key=lambda x: x.a, reverse=True)
    for i in range(min(m, len(v))):
        all_set.add(v[i])
    
    v.sort(key=lambda x: x.d, reverse=True)
    for i in range(min(m, len(v))):
        all_set.add(v[i])
    
    v.sort(key=lambda x: x.h, reverse=True)
    for i in range(min(m, len(v))):
        all_set.add(v[i])
    
    print(len(all_set))

if __name__ == "__main__":
    main()