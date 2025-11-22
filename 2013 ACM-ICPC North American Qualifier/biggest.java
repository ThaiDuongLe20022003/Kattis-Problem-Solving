import java.util.*;
import java.math.*;

public class biggest {
    static long gcd(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int numTestCases = scanner.nextInt();
        
        for (int t = 0; t < numTestCases; t++) {
            long r = scanner.nextLong();
            long n = scanner.nextLong();
            long d = scanner.nextLong();
            long m = scanner.nextLong();
            long s = scanner.nextLong();
            
            // Convert angle to rational form: theta = p/q degrees
            long thetaSeconds = 3600L * d + 60L * m + s;
            long denominator = 3600L;
            
            // Reduce the fraction
            long g = gcd(thetaSeconds, denominator);
            long p = thetaSeconds / g;  // numerator
            long q = denominator / g;   // denominator
            
            // Angles in rational form: (i * p) mod (360 * q) for i = 0, 1, ..., n-1
            long modulus = 360L * q;
            long g2 = gcd(p, modulus);
            long period = modulus / g2;
            
            // Number of distinct cuts
            long k = Math.min(n, period);
            
            double maxAngle;
            
            if (k == 1) {
                // Only one cut, entire pizza
                maxAngle = 360.0;
            } else {
                // Generate distinct cut positions
                List<Long> cuts = new ArrayList<>();
                
                for (long i = 0; i < k; i++) {
                    cuts.add((i * p) % modulus);
                }
                
                // Sort the cuts
                Collections.sort(cuts);
                
                // Find maximum gap
                long maxGap = 0;
                for (int i = 0; i < cuts.size() - 1; i++) {
                    maxGap = Math.max(maxGap, cuts.get(i + 1) - cuts.get(i));
                }
                // Check wrap-around gap
                maxGap = Math.max(maxGap, modulus - cuts.get(cuts.size() - 1) + cuts.get(0));
                
                // Convert to degrees
                maxAngle = (double) maxGap / q;
            }
            
            double area = (maxAngle / 360.0) * Math.PI * r * r;
            System.out.printf("%.10f\n", area);
        }
        
        scanner.close();
    }
}