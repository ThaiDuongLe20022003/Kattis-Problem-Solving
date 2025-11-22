using System;

class Program {
    static void Main() {
        int n = int.Parse(Console.ReadLine());
        
        for (int i = 0; i < n; i++) {
            int next = int.Parse(Console.ReadLine());
            
            if ((next & 1) == 1) {
                Console.WriteLine($"{next} is odd");
            } else {
                Console.WriteLine($"{next} is even");
            }
        }
    }
}