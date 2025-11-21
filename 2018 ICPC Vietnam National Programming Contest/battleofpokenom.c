#include <stdio.h>
#include <stdlib.h>

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int k;
        scanf("%d", &k);
        
        char* steps = malloc(2 * k * sizeof(char));
        for (int i = 0; i < 2 * k; i++) {
            scanf(" %c", &steps[i]);
        }
        
        int s = 0;
        int points[2] = {0, 0};
        int rounds[2] = {k, k};
        int end[2] = {-1, -1};
        
        for (; s < 2 * k; s++) {
            if (steps[s] == 'E') points[s & 1]++;
            rounds[s & 1]--;
            if (points[0] + rounds[0] < points[1] || points[1] + rounds[1] < points[0]) {
                end[~(s) & 1] = s++;
                break;
            }
        }
        
        for (int c = 0; c < s; c++) {
            char a = '_', b = '_';
            int found = 1;
            
            for (int i = c; i < s; i++) {
                if (end[i & 1] != i) {
                    if ((i & 1 ? a : b) != '_' && (i & 1 ? a : b) != steps[i]) {
                        found = 0;
                        break;
                    }
                    if (i & 1) a = steps[i];
                    else b = steps[i];
                }
            }
            
            if (found) {
                printf("%d %d\n", s, c);
                break;
            }
        }
        
        free(steps);
    }
    
    return 0;
}