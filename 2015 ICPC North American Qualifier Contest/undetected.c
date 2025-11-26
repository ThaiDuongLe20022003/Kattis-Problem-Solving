#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    int* p;
    int* rank;
    int* setSize;
    int numSets;
} UnionFind;

UnionFind* createUnionFind(int n) {
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    uf->p = (int*)malloc(n * sizeof(int));
    uf->rank = (int*)calloc(n, sizeof(int));
    uf->setSize = (int*)malloc(n * sizeof(int));
    uf->numSets = n;
    
    for (int i = 0; i < n; i++) {
        uf->p[i] = i;
        uf->setSize[i] = 1;
    }
    return uf;
}

int findSet(UnionFind* uf, int i) {
    return (uf->p[i] == i) ? i : (uf->p[i] = findSet(uf, uf->p[i]));
}

int isSameSet(UnionFind* uf, int i, int j) {
    return findSet(uf, i) == findSet(uf, j);
}

void unionSet(UnionFind* uf, int i, int j) {
    if (!isSameSet(uf, i, j)) {
        uf->numSets--;
        int x = findSet(uf, i);
        int y = findSet(uf, j);
        
        if (uf->rank[x] > uf->rank[y]) {
            uf->p[y] = x;
            uf->setSize[x] += uf->setSize[y];
        } else {
            uf->p[x] = y;
            uf->setSize[y] += uf->setSize[x];
            if (uf->rank[x] == uf->rank[y])
                uf->rank[y]++;
        }
    }
}

void freeUnionFind(UnionFind* uf) {
    free(uf->p);
    free(uf->rank);
    free(uf->setSize);
    free(uf);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* rads = (int*)malloc(n * sizeof(int));
    Point* coords = (Point*)malloc(n * sizeof(Point));
    
    for (int i = 0; i < n; i++) {
        int x, y, r;
        scanf("%d %d %d", &x, &y, &r);
        rads[i] = r;
        coords[i] = (Point){x, y};
    }
    
    UnionFind* uf = createUnionFind(n + 2);
    int i = 0;
    
    while (i < n) {
        // Check left wall collision
        if (coords[i].x - rads[i] < 0)
            unionSet(uf, 0, i + 2);
        // Check right wall collision
        if (coords[i].x + rads[i] > 200)
            unionSet(uf, 1, i + 2);
        
        // Check intersection with previous circles
        for (int j = 0; j < i; j++) {
            int dx = coords[i].x - coords[j].x;
            int dy = coords[i].y - coords[j].y;
            int r_sum = rads[i] + rads[j];
            
            if (dx * dx + dy * dy < r_sum * r_sum)
                unionSet(uf, i + 2, j + 2);
        }
        
        // Check if left and right walls are connected
        if (isSameSet(uf, 0, 1))
            break;
            
        i++;
    }
    
    printf("%d\n", i);
    
    free(rads);
    free(coords);
    freeUnionFind(uf);
    
    return 0;
}