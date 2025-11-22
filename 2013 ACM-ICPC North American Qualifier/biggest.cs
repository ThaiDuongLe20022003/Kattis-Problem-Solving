using System;
using System.Collections.Generic;

public class Program
{
    static long Gcd(long a, long b)
    {
        while (b != 0)
        {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    public static void Main()
    {
        int numTestCases = int.Parse(Console.ReadLine());
        
        for (int t = 0; t < numTestCases; t++)
        {
            string[] input = Console.ReadLine().Split();
            long r = long.Parse(input[0]);
            long n = long.Parse(input[1]);
            long d = long.Parse(input[2]);
            long m = long.Parse(input[3]);
            long s = long.Parse(input[4]);
            
            // Convert angle to rational form: theta = p/q degrees
            long thetaSeconds = 3600L * d + 60L * m + s;
            long denominator = 3600L;
            
            // Reduce the fraction
            long g = Gcd(thetaSeconds, denominator);
            long p = thetaSeconds / g;  // numerator
            long q = denominator / g;   // denominator
            
            // Angles in rational form: (i * p) mod (360 * q) for i = 0, 1, ..., n-1
            long modulus = 360L * q;
            long g2 = Gcd(p, modulus);
            long period = modulus / g2;
            
            // Number of distinct cuts
            long k = Math.Min(n, period);
            
            double maxAngle;
            
            if (k == 1)
            {
                // Only one cut, entire pizza
                maxAngle = 360.0;
            }
            else
            {
                // Generate distinct cut positions
                List<long> cuts = new List<long>();
                
                for (long i = 0; i < k; i++)
                {
                    cuts.Add((i * p) % modulus);
                }
                
                // Sort the cuts
                cuts.Sort();
                
                // Find maximum gap
                long maxGap = 0;
                for (int i = 0; i < cuts.Count - 1; i++)
                {
                    maxGap = Math.Max(maxGap, cuts[i + 1] - cuts[i]);
                }
                // Check wrap-around gap
                maxGap = Math.Max(maxGap, modulus - cuts[cuts.Count - 1] + cuts[0]);
                
                // Convert to degrees
                maxAngle = (double)maxGap / q;
            }
            
            double area = (maxAngle / 360.0) * Math.PI * r * r;
            Console.WriteLine($"{area:F10}");
        }
    }
}