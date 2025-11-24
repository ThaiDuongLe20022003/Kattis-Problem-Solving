#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef long long ll;

typedef struct {
    int u, v, id;
    ll cap;
} Edge;

typedef struct {
    int* parent;
    int n;
} DSU;

DSU* dsu_create(int n) {
    DSU* dsu = (DSU*)malloc(sizeof(DSU));
    dsu->n = n;
    dsu->parent = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
        dsu->parent[i] = i;
    }
    return dsu;
}

int dsu_find(DSU* dsu, int i) {
    if (dsu->parent[i] == i) return i;
    return dsu->parent[i] = dsu_find(dsu, dsu->parent[i]);
}

bool dsu_unite(DSU* dsu, int i, int j) {
    int root_i = dsu_find(dsu, i);
    int root_j = dsu_find(dsu, j);
    if (root_i != root_j) {
        dsu->parent[root_i] = root_j;
        return true;
    }
    return false;
}

void dsu_free(DSU* dsu) {
    free(dsu->parent);
    free(dsu);
}

// Comparison function for sorting edges
int compare_edges(const void* a, const void* b) {
    Edge* ea = (Edge*)a;
    Edge* eb = (Edge*)b;
    if (ea->cap > eb->cap) return -1;
    if (ea->cap < eb->cap) return 1;
    return 0;
}

typedef struct Node {
    int vertex;
    int road_id;
    struct Node* next;
} Node;

Node** adj;
Edge* all_edges;
ll* capacities;
int n, m, e;

bool check_path(int a, int b, ll w) {
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    int* queue = (int*)malloc((n + 1) * sizeof(int));
    int front = 0, rear = 0;
    
    queue[rear++] = a;
    visited[a] = true;
    
    while (front < rear) {
        int u = queue[front++];
        if (u == b) {
            free(visited);
            free(queue);
            return true;
        }
        
        Node* current = adj[u];
        while (current != NULL) {
            int v = current->vertex;
            int r_id = current->road_id;
            if (!visited[v] && capacities[r_id] >= w) {
                visited[v] = true;
                queue[rear++] = v;
            }
            current = current->next;
        }
    }
    
    free(visited);
    free(queue);
    return false;
}

void remove_from_adj(int u, int v, int r_id) {
    // Remove from u's list
    Node** prev = &adj[u];
    Node* current = adj[u];
    while (current != NULL) {
        if (current->vertex == v && current->road_id == r_id) {
            *prev = current->next;
            free(current);
            break;
        }
        prev = &current->next;
        current = current->next;
    }
    
    // Remove from v's list
    prev = &adj[v];
    current = adj[v];
    while (current != NULL) {
        if (current->vertex == u && current->road_id == r_id) {
            *prev = current->next;
            free(current);
            break;
        }
        prev = &current->next;
        current = current->next;
    }
}

typedef struct {
    ll min_cap;
    int min_road_id;
} BottleneckResult;

BottleneckResult find_path_bottleneck(int start, int end) {
    BottleneckResult result = {-1, -1};
    bool* visited = (bool*)calloc(n + 1, sizeof(bool));
    int* parent = (int*)calloc(n + 1, sizeof(int));
    int* road_to_parent = (int*)calloc(n + 1, sizeof(int));
    int* queue = (int*)malloc((n + 1) * sizeof(int));
    int front = 0, rear = 0;
    
    queue[rear++] = start;
    visited[start] = true;
    
    bool found = false;
    while (front < rear && !found) {
        int u = queue[front++];
        
        Node* current = adj[u];
        while (current != NULL) {
            int v = current->vertex;
            int r_id = current->road_id;
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                road_to_parent[v] = r_id;
                queue[rear++] = v;
                if (v == end) {
                    found = true;
                    break;
                }
            }
            current = current->next;
        }
    }
    
    if (!found) {
        result.min_cap = -1;
        result.min_road_id = -1;
    } else {
        ll min_cap = 1LL << 62;
        int min_road_id = -1;
        int curr = end;
        
        while (curr != start) {
            int r_id = road_to_parent[curr];
            if (capacities[r_id] < min_cap) {
                min_cap = capacities[r_id];
                min_road_id = r_id;
            }
            curr = parent[curr];
        }
        result.min_cap = min_cap;
        result.min_road_id = min_road_id;
    }
    
    free(visited);
    free(parent);
    free(road_to_parent);
    free(queue);
    return result;
}

void add_edge(int u, int v, int r_id) {
    Node* node1 = (Node*)malloc(sizeof(Node));
    node1->vertex = v;
    node1->road_id = r_id;
    node1->next = adj[u];
    adj[u] = node1;
    
    Node* node2 = (Node*)malloc(sizeof(Node));
    node2->vertex = u;
    node2->road_id = r_id;
    node2->next = adj[v];
    adj[v] = node2;
}

int main() {
    scanf("%d %d", &n, &m);
    
    adj = (Node**)calloc(n + 1, sizeof(Node*));
    all_edges = (Edge*)malloc((m + 1) * sizeof(Edge));
    capacities = (ll*)malloc((m + 1) * sizeof(ll));
    
    Edge* initial_edges = (Edge*)malloc(m * sizeof(Edge));
    for (int i = 1; i <= m; i++) {
        all_edges[i].id = i;
        scanf("%d %d %lld", &all_edges[i].u, &all_edges[i].v, &all_edges[i].cap);
        capacities[i] = all_edges[i].cap;
        initial_edges[i-1] = all_edges[i];
    }
    
    // Build initial MSF
    qsort(initial_edges, m, sizeof(Edge), compare_edges);
    DSU* dsu = dsu_create(n);
    
    for (int i = 0; i < m; i++) {
        Edge edge = initial_edges[i];
        if (dsu_unite(dsu, edge.u, edge.v)) {
            add_edge(edge.u, edge.v, edge.id);
        }
    }
    
    scanf("%d", &e);
    for (int i = 0; i < e; i++) {
        char type[2];
        scanf("%1s", type);
        
        if (type[0] == 'S') {
            int a, b;
            ll w;
            scanf("%d %d %lld", &a, &b, &w);
            printf("%d\n", check_path(a, b, w));
        } else {
            int r_id;
            ll c_new;
            scanf("%d %lld", &r_id, &c_new);
            ll c_old = capacities[r_id];
            capacities[r_id] = c_new;
            int u = all_edges[r_id].u;
            int v = all_edges[r_id].v;
            
            // Check if edge was in MSF
            bool was_in_msf = false;
            Node* current = adj[u];
            while (current != NULL) {
                if (current->vertex == v && current->road_id == r_id) {
                    was_in_msf = true;
                    break;
                }
                current = current->next;
            }
            
            if (was_in_msf && c_new < c_old) {
                remove_from_adj(u, v, r_id);
                
                // Find component containing u
                bool* in_T_u = (bool*)calloc(n + 1, sizeof(bool));
                int* queue = (int*)malloc((n + 1) * sizeof(int));
                int front = 0, rear = 0;
                queue[rear++] = u;
                in_T_u[u] = true;
                
                while (front < rear) {
                    int curr = queue[front++];
                    Node* node = adj[curr];
                    while (node != NULL) {
                        if (!in_T_u[node->vertex]) {
                            in_T_u[node->vertex] = true;
                            queue[rear++] = node->vertex;
                        }
                        node = node->next;
                    }
                }
                
                // Find best replacement edge
                ll max_cap = -1;
                int best_r_id = -1;
                for (int j = 1; j <= m; j++) {
                    if (in_T_u[all_edges[j].u] != in_T_u[all_edges[j].v]) {
                        if (capacities[j] > max_cap) {
                            max_cap = capacities[j];
                            best_r_id = j;
                        }
                    }
                }
                
                if (best_r_id != -1) {
                    add_edge(all_edges[best_r_id].u, all_edges[best_r_id].v, best_r_id);
                }
                
                free(in_T_u);
                free(queue);
            } else if (!was_in_msf && c_new > c_old) {
                BottleneckResult bottleneck = find_path_bottleneck(u, v);
                if (bottleneck.min_cap != -1 && c_new > bottleneck.min_cap) {
                    remove_from_adj(all_edges[bottleneck.min_road_id].u, 
                                   all_edges[bottleneck.min_road_id].v, 
                                   bottleneck.min_road_id);
                    add_edge(u, v, r_id);
                }
            }
        }
    }
    
    // Cleanup
    dsu_free(dsu);
    free(initial_edges);
    for (int i = 1; i <= n; i++) {
        Node* current = adj[i];
        while (current != NULL) {
            Node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(adj);
    free(all_edges);
    free(capacities);
    
    return 0;
}