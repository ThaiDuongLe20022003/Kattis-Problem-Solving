#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Comparison function for qsort (descending order)
int compare_desc(const void* a, const void* b) {
    long long aa = *(const long long*)a;
    long long bb = *(const long long*)b;
    if (aa > bb) return -1;
    if (aa < bb) return 1;
    return 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int first_case = 1;
    while (n--) {
        if (!first_case) {
            printf("\n");
        }
        first_case = 0;
        
        long long x;
        scanf("%lld", &x);
        
        long long left_weights[100];
        long long right_weights[100];
        int left_count = 0;
        int right_count = 0;
        long long current_power_of_3 = 1;
        
        while (x > 0) {
            int rem = x % 3;
            if (rem == 1) {
                right_weights[right_count++] = current_power_of_3;
                x -= 1;
            } else if (rem == 2) {
                left_weights[left_count++] = current_power_of_3;
                x += 1;
            }
            
            x /= 3;
            if (x > 0) {
                if (current_power_of_3 > LLONG_MAX / 3) {
                    break;
                }
                current_power_of_3 *= 3;
            }
        }
        
        // Sort in descending order
        qsort(left_weights, left_count, sizeof(long long), compare_desc);
        qsort(right_weights, right_count, sizeof(long long), compare_desc);
        
        // Print results
        printf("left pan:");
        for (int i = 0; i < left_count; i++) {
            printf(" %lld", left_weights[i]);
        }
        printf("\n");
        
        printf("right pan:");
        for (int i = 0; i < right_count; i++) {
            printf(" %lld", right_weights[i]);
        }
        printf("\n");
    }
    
    return 0;
}