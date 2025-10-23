#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200000

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* graph[MAX_N + 1];
int visited[MAX_N + 1];
int stack[MAX_N];
int top = -1;

void add_edge(int u, int v) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->vertex = v;
    new_node->next = graph[u];
    graph[u] = new_node;
}

void dfs_iterative(int start) {
    stack[++top] = start;
    visited[start] = 1;
    
    while (top >= 0) {
        int u = stack[top--];
        Node* curr = graph[u];
        while (curr != NULL) {
            int v = curr->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                stack[++top] = v;
            }
            curr = curr->next;
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    // Initialize graph
    for (int i = 1; i <= N; i++) {
        graph[i] = NULL;
        visited[i] = 0;
    }
    
    // Read edges
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    
    // DFS from house 1
    dfs_iterative(1);
    
    // Check if all visited
    int all_connected = 1;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            all_connected = 0;
            break;
        }
    }
    
    if (all_connected) {
        printf("Connected\n");
    } else {
        for (int i = 1; i <= N; i++) {
            if (!visited[i]) {
                printf("%d\n", i);
            }
        }
    }
    
    // Free memory
    for (int i = 1; i <= N; i++) {
        Node* curr = graph[i];
        while (curr != NULL) {
            Node* temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    
    return 0;
}