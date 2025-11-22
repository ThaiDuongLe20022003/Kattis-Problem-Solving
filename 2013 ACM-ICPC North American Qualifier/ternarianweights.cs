using System;
using System.Collections.Generic;

public class Program
{
    public static void Main()
    {
        int n = int.Parse(Console.ReadLine());
        bool firstCase = true;
        
        while (n-- > 0)
        {
            if (!firstCase)
            {
                Console.WriteLine();
            }
            firstCase = false;
            
            long x = long.Parse(Console.ReadLine());
            
            List<long> leftWeights = new List<long>();
            List<long> rightWeights = new List<long>();
            long currentPowerOf3 = 1;
            
            while (x > 0)
            {
                int rem = (int)(x % 3);
                if (rem == 1)
                {
                    rightWeights.Add(currentPowerOf3);
                    x -= 1;
                }
                else if (rem == 2)
                {
                    leftWeights.Add(currentPowerOf3);
                    x += 1;
                }
                
                x /= 3;
                if (x > 0)
                {
                    if (currentPowerOf3 > long.MaxValue / 3)
                    {
                        break;
                    }
                    currentPowerOf3 *= 3;
                }
            }
            
            // Sort in descending order
            leftWeights.Sort((a, b) => b.CompareTo(a));
            rightWeights.Sort((a, b) => b.CompareTo(a));
            
            // Print results
            Console.Write("left pan:");
            foreach (long weight in leftWeights)
            {
                Console.Write($" {weight}");
            }
            Console.WriteLine();
            
            Console.Write("right pan:");
            foreach (long weight in rightWeights)
            {
                Console.Write($" {weight}");
            }
            Console.WriteLine();
        }
    }
}