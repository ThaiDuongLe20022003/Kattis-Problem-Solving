#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int compare(const void* a, const void* b) {
    long long aa = *(const long long*)a;
    long long bb = *(const long long*)b;
    if (aa < bb) return -1;
    if (aa > bb) return 1;
    return 0;
}

int main() {
    int num_test_cases;
    scanf("%d", &num_test_cases);
    
    while (num_test_cases--) {
        long long r, n, d, m, s;
        scanf("%lld %lld %lld %lld %lld", &r, &n, &d, &m, &s);
        
        // Convert angle to rational form: theta = p/q degrees
        long long theta_seconds = 3600LL * d + 60LL * m + s;
        long long denominator = 3600LL;
        
        // Reduce the fraction
        long long g = gcd(theta_seconds, denominator);
        long long p = theta_seconds / g;  // numerator
        long long q = denominator / g;     // denominator
        
        // Angles in rational form: (i * p) mod (360 * q) for i = 0, 1, ..., n-1
        long long modulus = 360LL * q;
        long long g2 = gcd(p, modulus);
        long long period = modulus / g2;
        
        // Number of distinct cuts
        long long k = n < period ? n : period;
        
        double max_angle;
        
        if (k == 1) {
            // Only one cut, entire pizza
            max_angle = 360.0;
        } else {
            // Generate distinct cut positions
            long long* cuts = (long long*)malloc(k * sizeof(long long));
            
            for (long long i = 0; i < k; i++) {
                cuts[i] = (i * p) % modulus;
            }
            
            // Sort the cuts
            qsort(cuts, k, sizeof(long long), compare);
            
            // Find maximum gap
            long long max_gap = 0;
            for (long long i = 0; i < k - 1; i++) {
                long long gap = cuts[i+1] - cuts[i];
                if (gap > max_gap) {
                    max_gap = gap;
                }
            }
            // Check wrap-around gap
            long long wrap_gap = modulus - cuts[k-1] + cuts[0];
            if (wrap_gap > max_gap) {
                max_gap = wrap_gap;
            }
            
            // Convert to degrees
            max_angle = (double)max_gap / q;
            
            free(cuts);
        }
        
        double area = (max_angle / 360.0) * acos(-1.0) * r * r;
        printf("%.10f\n", area);
    }
    
    return 0;
}