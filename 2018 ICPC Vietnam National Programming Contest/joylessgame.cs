using System;

class Program {
    static void Main() {
        int ntests = int.Parse(Console.ReadLine());
        string fi = "Chikapu";
        string se = "Bash";
        
        for (int i = 0; i < ntests; i++) {
            string s = Console.ReadLine();
            int n = s.Length;
            
            if (s[0] != s[n - 1]) {
                Console.WriteLine((n % 2 == 0) ? se : fi);
            } else {
                Console.WriteLine((n % 2 == 1) ? se : fi);
            }
        }
    }
}