import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def main():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    idx = 0
    num_test_cases = int(data[idx])
    idx += 1
    
    results = []
    
    for _ in range(num_test_cases):
        r = int(data[idx]); idx += 1
        n = int(data[idx]); idx += 1
        d = int(data[idx]); idx += 1
        m = int(data[idx]); idx += 1
        s = int(data[idx]); idx += 1
        
        # Convert angle to rational form: theta = p/q degrees
        theta_seconds = 3600 * d + 60 * m + s
        denominator = 3600
        
        # Reduce the fraction
        g = gcd(theta_seconds, denominator)
        p = theta_seconds // g  # numerator
        q = denominator // g     # denominator
        
        # Angles in rational form: (i * p) mod (360 * q) for i = 0, 1, ..., n-1
        modulus = 360 * q
        g2 = gcd(p, modulus)
        period = modulus // g2
        
        # Number of distinct cuts
        k = min(n, period)
        
        if k == 1:
            # Only one cut, entire pizza
            max_angle = 360.0
        else:
            # Generate distinct cut positions
            cuts = []
            for i in range(k):
                cuts.append((i * p) % modulus)
            
            # Sort the cuts
            cuts.sort()
            
            # Find maximum gap
            max_gap = 0
            for i in range(len(cuts) - 1):
                max_gap = max(max_gap, cuts[i + 1] - cuts[i])
            # Check wrap-around gap
            max_gap = max(max_gap, modulus - cuts[-1] + cuts[0])
            
            # Convert to degrees
            max_angle = max_gap / q
        
        area = (max_angle / 360.0) * math.pi * r * r
        results.append(f"{area:.10f}")
    
    print("\n".join(results))

if __name__ == "__main__":
    main()