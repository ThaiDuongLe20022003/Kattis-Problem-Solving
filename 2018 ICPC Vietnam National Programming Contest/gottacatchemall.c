#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
} Pair;

int comparePairs(const void *a, const void *b) {
    Pair *p1 = (Pair *)a;
    Pair *p2 = (Pair *)b;
    if (p1->first != p2->first) return p1->first - p2->first;
    return p1->second - p2->second;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Pair *junctions = malloc((n - 1) * sizeof(Pair));
    for (int i = 0; i < n - 1; i++) {
        scanf("%d %d", &junctions[i].first, &junctions[i].second);
        if (junctions[i].first > junctions[i].second) {
            int temp = junctions[i].first;
            junctions[i].first = junctions[i].second;
            junctions[i].second = temp;
        }
    }
    
    qsort(junctions, n - 1, sizeof(Pair), comparePairs);
    
    int unique_count = 0;
    for (int i = 0; i < n - 1; i++) {
        if (i == 0 || junctions[i].first != junctions[i-1].first || junctions[i].second != junctions[i-1].second) {
            junctions[unique_count++] = junctions[i];
        }
    }
    
    int *count = calloc(n + 1, sizeof(int));
    for (int i = 0; i < unique_count; i++) {
        count[junctions[i].first]++;
        count[junctions[i].second]++;
    }
    
    int **connected = malloc((n + 1) * sizeof(int *));
    int *connected_size = calloc(n + 1, sizeof(int));
    for (int i = 1; i <= n; i++) {
        connected[i] = malloc(count[i] * sizeof(int));
    }
    
    for (int i = 0; i < unique_count; i++) {
        int u = junctions[i].first;
        int v = junctions[i].second;
        if (count[u] != count[v] ? count[u] > count[v] : u < v) {
            connected[u][connected_size[u]++] = v;
        } else {
            connected[v][connected_size[v]++] = u;
        }
    }
    
    int *visited = calloc(n + 1, sizeof(int));
    long long total = 0, optimal = 0;
    
    for (int i = 1; i <= n; i++) {
        if (count[i] > 0) {
            total += (long long)count[i] * (count[i] - 1);
        }
        for (int j = 0; j < connected_size[i]; j++) {
            visited[connected[i][j]] = i;
        }
        for (int j = 0; j < connected_size[i]; j++) {
            int neighbor = connected[i][j];
            for (int k = 0; k < connected_size[neighbor]; k++) {
                int third = connected[neighbor][k];
                if (visited[third] == i) {
                    optimal++;
                }
            }
        }
    }
    
    printf("%lld\n", total - 6 * optimal);
    
    free(junctions);
    free(count);
    for (int i = 1; i <= n; i++) {
        free(connected[i]);
    }
    free(connected);
    free(connected_size);
    free(visited);
    
    return 0;
}