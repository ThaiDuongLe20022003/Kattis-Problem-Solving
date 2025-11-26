using System;

class Program {
    static void Main() {
        int times = int.Parse(Console.ReadLine());
        
        for(int i = 0; i < times; i++) {
            string s = Console.ReadLine();
            
            if(s.StartsWith("Simon says")) {
                string result = s.Substring(11);
                Console.WriteLine(result);
            }
        }
    }
}