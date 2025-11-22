import math

def is_prime(n):
    if n == 1:
        return False
    for i in range(2, int(math.sqrt(n)) + 1):
        if n % i == 0:
            return False
    return True

def main():
    primes = [2]
    
    for i in range(3, 32000, 2):
        if is_prime(i):
            primes.append(i)
    
    cases = int(input())
    
    for zax in range(cases):
        count = 0
        str_result = ""
        num = int(input())
        
        for i in range(len(primes)):
            low = primes[i]
            high = num - primes[i]
            
            if high < low:
                break
            
            if high in primes:
                count += 1
                str_result += f"{low}+{high}\n"
        
        print(f"{num} has {count} representation(s)")
        print(str_result, end="")

if __name__ == "__main__":
    main()