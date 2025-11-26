using System;

class Program {
    static void Main() {
        int n = int.Parse(Console.ReadLine());
        
        for(int i = 0; i < n; i++) {
            bool[] letters = new bool[26];
            string s = Console.ReadLine();
            int used = 0;
            
            foreach(char c in s) {
                int temp = char.ToLower(c) - 'a';
                if(temp < 26 && temp >= 0 && !letters[temp]) {
                    letters[temp] = true;
                    used++;
                }
            }
            
            if(used == 26) {
                Console.Write("pangram");
            } else {
                Console.Write("missing ");
                for(int j = 0; j < 26; j++) {
                    if(!letters[j]) {
                        Console.Write((char)(j + 'a'));
                    }
                }
            }
            
            Console.WriteLine();
        }
    }
}