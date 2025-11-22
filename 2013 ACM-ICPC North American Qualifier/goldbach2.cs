using System;
using System.Collections.Generic;

class Goldbach2 {
    static bool IsPrime(int n) {
        if (n == 1) return false;
        for (int i = 2; i < (int)(Math.Sqrt(n) + 1); i++)
            if (n % i == 0)
                return false;
        return true;
    }
    
    static void Main() {
        List<int> primes = new List<int>();
        primes.Add(2);
        
        for (int i = 3; i < 32000; i += 2)
            if (IsPrime(i))
                primes.Add(i);
        
        int cases = int.Parse(Console.ReadLine());
        
        for (int zax = 0; zax < cases; zax++) {
            int count = 0;
            string str = "";
            int num = int.Parse(Console.ReadLine());
            
            for (int i = 0; i < primes.Count; i++) {
                int low = primes[i];
                int high = num - primes[i];
                
                if (high < low)
                    break;
                
                if (primes.Contains(high)) {
                    count++;
                    str += low + "+" + high + "\n";
                }
            }
            
            Console.WriteLine(num + " has " + count + " representation(s)");
            Console.Write(str);
        }
    }
}