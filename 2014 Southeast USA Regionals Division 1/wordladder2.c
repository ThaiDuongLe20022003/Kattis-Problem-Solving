#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 1000
#define MAX_LEN 20
#define INF 1000000000

typedef struct {
    int first, second;
} ti2;

typedef struct {
    int first, second, third;
} ti3;

int N;
char words[MAX_N][MAX_LEN];
int D[MAX_N][MAX_N];

int word_dist(int a, int b) {
    int res = 0;
    int len = strlen(words[a]);
    for (int i = 0; i < len; ++i) {
        if (words[a][i] != words[b][i]) ++res;
    }
    return res;
}

void diffs(int a, int b, char res[2][MAX_LEN]) {
    int pos[2], idx = 0;
    int len = strlen(words[a]);
    for (int i = 0; i < len; ++i) {
        if (words[a][i] != words[b][i]) {
            pos[idx++] = i;
        }
    }
    
    strcpy(res[0], words[a]);
    res[0][pos[0]] = words[b][pos[0]];
    
    strcpy(res[1], words[a]);
    res[1][pos[1]] = words[b][pos[1]];
}

char* solve(ti2* pairs, int pairs_count) {
    static char res[MAX_LEN];
    res[0] = '\0';
    
    for (int i = 0; i < pairs_count; ++i) {
        int a = pairs[i].first;
        int b = pairs[i].second;
        char temp[2][MAX_LEN];
        diffs(a, b, temp);
        
        if (res[0] == '\0') {
            strcpy(res, temp[0]);
        }
        if (strcmp(temp[0], res) < 0) {
            strcpy(res, temp[0]);
        }
        if (strcmp(temp[1], res) < 0) {
            strcpy(res, temp[1]);
        }
    }
    return res;
}

int trace(int dist[][2], int cur, ti2* pairs, int* pairs_count) {
    *pairs_count = 0;
    int queue[MAX_N];
    int front = 0, rear = 0;
    queue[rear++] = cur;
    
    while (front < rear) {
        cur = queue[front++];
        for (int i = 0; i < N; ++i) {
            int d = D[i][cur];
            if (d > 2) continue;
            if (d == 2 && dist[i][0] + d == dist[cur][1]) {
                pairs[*pairs_count].first = i;
                pairs[*pairs_count].second = cur;
                (*pairs_count)++;
            }
            if (d == 1 && dist[i][1] + d == dist[cur][1]) {
                queue[rear++] = i;
            }
        }
    }
    return *pairs_count;
}

int dijkstra(int src, int dest, ti2* pairs, int* pairs_count) {
    int dist[MAX_N][2];
    for (int i = 0; i < N; ++i) {
        dist[i][0] = INF;
        dist[i][1] = INF;
    }
    
    // Simple queue simulation for priority queue
    ti3 queue[MAX_N * 2];
    int size = 0;
    
    dist[src][0] = 0;
    queue[size].first = 0;
    queue[size].second = 0;
    queue[size].third = src;
    size++;
    
    while (size > 0) {
        // Find min element (simple min search)
        int min_idx = 0;
        for (int i = 1; i < size; ++i) {
            if (queue[i].first < queue[min_idx].first) {
                min_idx = i;
            }
        }
        
        int s = queue[min_idx].first;
        int k = queue[min_idx].second;
        int cur = queue[min_idx].third;
        
        // Remove element
        for (int i = min_idx; i < size - 1; ++i) {
            queue[i] = queue[i + 1];
        }
        size--;
        
        for (int nxt = 0; nxt < N; ++nxt) {
            int d = D[cur][nxt];
            int nk = (d == 2);
            if (d > 2 || (nk && k)) continue;
            if (k) nk = 1;
            
            if (s + d < dist[nxt][nk]) {
                dist[nxt][nk] = s + d;
                queue[size].first = s + d;
                queue[size].second = (d == 2) ? 1 : k;
                queue[size].third = nxt;
                size++;
            }
        }
    }
    
    if (dist[dest][0] <= dist[dest][1]) {
        return dist[dest][0];
    }
    
    *pairs_count = trace(dist, dest, pairs, pairs_count);
    return dist[dest][1];
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%s", words[i]);
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            D[i][j] = INF;
        }
    }
    
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            D[i][j] = D[j][i] = word_dist(i, j);
        }
    }
    
    ti2 pairs[MAX_N];
    int pairs_count;
    int steps = dijkstra(0, 1, pairs, &pairs_count);
    
    if (steps == INF || pairs_count == 0) {
        printf("0\n");
    } else {
        printf("%s\n", solve(pairs, pairs_count));
    }
    printf("%d\n", (steps == INF) ? -1 : steps);
    
    return 0;
}