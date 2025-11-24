#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int pos, strength, idx;
} Fence;

int compare(const void *a, const void *b) {
    Fence *fa = (Fence*)a;
    Fence *fb = (Fence*)b;
    return fa->pos - fb->pos;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Fence *fences = malloc(n * sizeof(Fence));
    int *l = malloc(n * sizeof(int));
    int *r = malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &fences[i].pos, &fences[i].strength);
        fences[i].idx = l[i] = r[i] = i;
    }
    
    qsort(fences, n, sizeof(Fence), compare);
    
    bool change;
    do {
        change = false;
        
        // Forward pass
        int *stack = malloc(n * sizeof(int));
        int top = -1;
        
        for (int i = 0; i < n; i++) {
            while (top >= 0 && abs(fences[i].pos - fences[stack[top]].pos) <= fences[i].strength) {
                int j = stack[top];
                top--;
                
                if (l[i] > l[j]) {
                    l[i] = l[j];
                    change = true;
                }
                if (r[i] < r[j]) {
                    r[i] = r[j];
                    change = true;
                }
            }
            stack[++top] = i;
        }
        free(stack);
        
        // Backward pass
        stack = malloc(n * sizeof(int));
        top = -1;
        
        for (int i = n - 1; i >= 0; i--) {
            while (top >= 0 && abs(fences[i].pos - fences[stack[top]].pos) <= fences[i].strength) {
                int j = stack[top];
                top--;
                
                if (l[i] > l[j]) {
                    l[i] = l[j];
                    change = true;
                }
                if (r[i] < r[j]) {
                    r[i] = r[j];
                    change = true;
                }
            }
            stack[++top] = i;
        }
        free(stack);
        
    } while (change);
    
    int *cans = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        cans[fences[i].idx] = r[i] - l[i] + 1;
    }
    
    for (int i = 0; i < n; i++) {
        printf("%d ", cans[i]);
    }
    printf("\n");
    
    free(fences);
    free(l);
    free(r);
    free(cans);
    
    return 0;
}