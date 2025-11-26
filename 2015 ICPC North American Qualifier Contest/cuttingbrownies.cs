using System;

class Program {
    static bool[,] win = new bool[501, 501];
    
    static void Main() {
        // Precompute win states
        for (int i = 1; i <= 500; i++) {
            for (int j = 1; j <= 500; j++) {
                win[i, j] = false;
                
                for (int k = 1; k < j; k++) {
                    win[i, j] = win[i, j] || (!win[k, i] && !win[j - k, i]);
                }
            }
        }

        int n = int.Parse(Console.ReadLine());
        
        for (int i = 0; i < n; i++) {
            string[] parts = Console.ReadLine().Split();
            int b = int.Parse(parts[0]);
            int d = int.Parse(parts[1]);
            string s = parts[2];
            
            Console.Write(s + " ");
            if (s[0] == 'H') {
                Console.WriteLine(win[b, d] ? "can win" : "cannot win");
            } else {
                Console.WriteLine(win[d, b] ? "can win" : "cannot win");
            }
        }
    }
}