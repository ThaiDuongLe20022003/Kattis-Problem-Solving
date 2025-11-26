#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int time;
    int mask;
    int cloak;
} State;

// Min-heap implementation
typedef struct {
    State* data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPQ(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (State*)malloc(capacity * sizeof(State));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void swap(State* a, State* b) {
    State temp = *a;
    *a = *b;
    *b = temp;
}

void push(PriorityQueue* pq, State state) {
    if (pq->size >= pq->capacity) return;
    
    pq->data[pq->size] = state;
    int i = pq->size;
    pq->size++;
    
    while (i > 0 && pq->data[(i-1)/2].time > pq->data[i].time) {
        swap(&pq->data[(i-1)/2], &pq->data[i]);
        i = (i-1)/2;
    }
}

State pop(PriorityQueue* pq) {
    State result = pq->data[0];
    pq->size--;
    pq->data[0] = pq->data[pq->size];
    
    int i = 0;
    while (1) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int smallest = i;
        
        if (left < pq->size && pq->data[left].time < pq->data[smallest].time)
            smallest = left;
        if (right < pq->size && pq->data[right].time < pq->data[smallest].time)
            smallest = right;
            
        if (smallest == i) break;
        
        swap(&pq->data[i], &pq->data[smallest]);
        i = smallest;
    }
    
    return result;
}

int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

void freePQ(PriorityQueue* pq) {
    free(pq->data);
    free(pq);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* times = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &times[i]);
    }
    
    int states = 1 << n;
    int** dp = (int**)malloc(states * sizeof(int*));
    for (int i = 0; i < states; i++) {
        dp[i] = (int*)malloc(2 * sizeof(int));
        dp[i][0] = INF;
        dp[i][1] = INF;
    }
    
    // Initial state: everyone at gate, cloak at gate
    dp[0][0] = 0;
    
    PriorityQueue* pq = createPQ(states * 2);
    push(pq, (State){0, 0, 0});
    
    while (!isEmpty(pq)) {
        State current = pop(pq);
        int time = current.time;
        int mask = current.mask;
        int cloak = current.cloak;
        
        if (time > dp[mask][cloak]) {
            continue;
        }
        
        // Goal: everyone at dorm
        if (mask == (1 << n) - 1) {
            printf("%d\n", time);
            
            // Cleanup
            for (int i = 0; i < states; i++) {
                free(dp[i]);
            }
            free(dp);
            free(times);
            freePQ(pq);
            return 0;
        }
        
        if (cloak == 0) {
            // Cloak at gate: send people from gate to dorm
            
            // Send 1 person
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    int new_mask = mask | (1 << i);
                    int new_time = time + times[i];
                    if (new_time < dp[new_mask][1]) {
                        dp[new_mask][1] = new_time;
                        push(pq, (State){new_time, new_mask, 1});
                    }
                }
            }
            
            // Send 2 people
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) {
                    for (int j = i + 1; j < n; j++) {
                        if (!(mask & (1 << j))) {
                            int new_mask = mask | (1 << i) | (1 << j);
                            int new_time = time + MAX(times[i], times[j]);
                            if (new_time < dp[new_mask][1]) {
                                dp[new_mask][1] = new_time;
                                push(pq, (State){new_time, new_mask, 1});
                            }
                        }
                    }
                }
            }
        } else {
            // Cloak at dorm: send people from dorm to gate
            
            // Send 1 person back
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    int new_mask = mask ^ (1 << i);
                    int new_time = time + times[i];
                    if (new_time < dp[new_mask][0]) {
                        dp[new_mask][0] = new_time;
                        push(pq, (State){new_time, new_mask, 0});
                    }
                }
            }
            
            // Send 2 people back
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    for (int j = i + 1; j < n; j++) {
                        if (mask & (1 << j)) {
                            int new_mask = mask ^ (1 << i) ^ (1 << j);
                            int new_time = time + MAX(times[i], times[j]);
                            if (new_time < dp[new_mask][0]) {
                                dp[new_mask][0] = new_time;
                                push(pq, (State){new_time, new_mask, 0});
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Cleanup
    for (int i = 0; i < states; i++) {
        free(dp[i]);
    }
    free(dp);
    free(times);
    freePQ(pq);
    
    return 0;
}