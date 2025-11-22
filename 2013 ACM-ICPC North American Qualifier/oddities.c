#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        int next;
        scanf("%d", &next);
        
        if (next & 1 == 1) {
            printf("%d is odd\n", next);
        } else {
            printf("%d is even\n", next);
        }
    }
    
    return 0;
}