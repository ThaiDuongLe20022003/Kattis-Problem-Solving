#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 1002
#define MAX_EDGES 600000

typedef struct {
    int u, rev;
    int cap, initial_cap;
} Arc;

typedef struct {
    Arc* edges;
    int size;
    int capacity;
} EdgeList;

typedef struct {
    EdgeList network[MAX_NODES];
    int dist[MAX_NODES];
    int iter[MAX_NODES];
    int n;
} FlowNetwork;

void init_flow_network(FlowNetwork* fn, int n) {
    fn->n = n;
    for (int i = 0; i < n; i++) {
        fn->network[i].edges = NULL;
        fn->network[i].size = 0;
        fn->network[i].capacity = 0;
    }
}

void add_edge(FlowNetwork* fn, int u, int v, int cap_uv, int cap_vu) {
    if (u == v) return;
    
    // Add edge u->v
    if (fn->network[u].size == fn->network[u].capacity) {
        fn->network[u].capacity = fn->network[u].capacity == 0 ? 4 : fn->network[u].capacity * 2;
        fn->network[u].edges = realloc(fn->network[u].edges, fn->network[u].capacity * sizeof(Arc));
    }
    Arc arc_uv = {v, fn->network[v].size, cap_uv, cap_uv};
    fn->network[u].edges[fn->network[u].size++] = arc_uv;
    
    // Add edge v->u
    if (fn->network[v].size == fn->network[v].capacity) {
        fn->network[v].capacity = fn->network[v].capacity == 0 ? 4 : fn->network[v].capacity * 2;
        fn->network[v].edges = realloc(fn->network[v].edges, fn->network[v].capacity * sizeof(Arc));
    }
    Arc arc_vu = {u, fn->network[u].size - 1, cap_vu, cap_vu};
    fn->network[v].edges[fn->network[v].size++] = arc_vu;
}

int bfs(FlowNetwork* fn, int s, int t) {
    for (int i = 0; i < fn->n; i++) {
        fn->dist[i] = -1;
    }
    fn->dist[s] = 0;
    
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    queue[rear++] = s;
    
    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < fn->network[v].size; i++) {
            Arc* arc = &fn->network[v].edges[i];
            if (arc->cap > 0 && fn->dist[arc->u] == -1) {
                fn->dist[arc->u] = fn->dist[v] + 1;
                queue[rear++] = arc->u;
            }
        }
    }
    return fn->dist[t] != -1;
}

int dfs(FlowNetwork* fn, int v, int t, int flow) {
    if (v == t) return flow;
    
    for (; fn->iter[v] < fn->network[v].size; fn->iter[v]++) {
        Arc* arc = &fn->network[v].edges[fn->iter[v]];
        if (arc->cap > 0 && fn->dist[arc->u] == fn->dist[v] + 1) {
            int f = dfs(fn, arc->u, t, flow < arc->cap ? flow : arc->cap);
            if (f > 0) {
                arc->cap -= f;
                Arc* rev_arc = &fn->network[arc->u].edges[arc->rev];
                rev_arc->cap += f;
                return f;
            }
        }
    }
    return 0;
}

int max_flow(FlowNetwork* fn, int s, int t) {
    int flow = 0;
    int f;
    
    while (bfs(fn, s, t)) {
        for (int i = 0; i < fn->n; i++) {
            fn->iter[i] = 0;
        }
        while ((f = dfs(fn, s, t, INT_MAX)) > 0) {
            flow += f;
        }
    }
    return flow;
}

void free_flow_network(FlowNetwork* fn) {
    for (int i = 0; i < fn->n; i++) {
        if (fn->network[i].edges) {
            free(fn->network[i].edges);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    FlowNetwork fn;
    init_flow_network(&fn, 1002);
    int s = 1000, t = 1001;
    
    // Build the 3D grid network
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                int u = i * 100 + j * 10 + k;
                add_edge(&fn, u, (i > 0 ? (i - 1) * 100 + j * 10 + k : t), 1, 0);
                add_edge(&fn, u, (i < 9 ? (i + 1) * 100 + j * 10 + k : t), 1, 0);
                add_edge(&fn, u, (j > 0 ? i * 100 + (j - 1) * 10 + k : t), 1, 0);
                add_edge(&fn, u, (j < 9 ? i * 100 + (j + 1) * 10 + k : t), 1, 0);
                add_edge(&fn, u, (k > 0 ? i * 100 + j * 10 + (k - 1) : t), 1, 0);
                add_edge(&fn, u, (k < 9 ? i * 100 + j * 10 + (k + 1) : t), 1, 0);
            }
        }
    }
    
    // Add source connections
    for (int i = 0; i < n; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add_edge(&fn, s, x * 100 + y * 10 + z, 6, 0);
    }
    
    int result = max_flow(&fn, s, t);
    printf("%d\n", result);
    
    free_flow_network(&fn);
    return 0;
}