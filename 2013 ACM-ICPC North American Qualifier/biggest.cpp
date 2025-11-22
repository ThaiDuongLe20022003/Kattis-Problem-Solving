#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

long long gcd(long long a, long long b) {
    while (b) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int num_test_cases;
    cin >> num_test_cases;
    
    while (num_test_cases--) {
        long long r, n, d, m, s;
        cin >> r >> n >> d >> m >> s;
        
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
        long long k = min(n, period);
        
        double max_angle;
        
        if (k == 1) {
            // Only one cut, entire pizza
            max_angle = 360.0;
        } else {
            // Generate distinct cut positions
            // The cuts are at: 0, p, 2p, 3p, ..., (k-1)p (mod modulus)
            // We need to find the maximum gap between consecutive cuts
            
            vector<long long> cuts;
            cuts.reserve(k);
            
            for (long long i = 0; i < k; i++) {
                cuts.push_back((i * p) % modulus);
            }
            
            // Sort the cuts
            sort(cuts.begin(), cuts.end());
            
            // Find maximum gap
            long long max_gap = 0;
            for (size_t i = 0; i < cuts.size() - 1; i++) {
                max_gap = max(max_gap, cuts[i+1] - cuts[i]);
            }
            // Check wrap-around gap
            max_gap = max(max_gap, modulus - cuts.back() + cuts[0]);
            
            // Convert to degrees
            max_angle = (double)max_gap / q;
        }
        
        double area = (max_angle / 360.0) * M_PI * r * r;
        cout << fixed << setprecision(10) << area << endl;
    }
    
    return 0;
}