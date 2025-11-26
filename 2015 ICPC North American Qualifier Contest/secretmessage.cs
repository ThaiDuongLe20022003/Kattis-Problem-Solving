using System;

class SecretMessage {
    static void Main() {
        int testcases = int.Parse(Console.ReadLine());
        
        for (int zaxbys = 0; zaxbys < testcases; zaxbys++) {
            string str = Console.ReadLine();
            
            int i = 1;
            int length = str.Length;
            
            while (i * i < length)
                i++;
            
            // Pad string with asterisks
            int paddedLength = i * i;
            string paddedStr = str;
            for (int x = length; x < paddedLength; x++)
                paddedStr += "*";
            
            // Create 2D array
            char[,] nums = new char[i, i];
            
            // Fill 2D array
            for (int r = 0; r < i; r++)
                for (int c = 0; c < i; c++)
                    nums[r, c] = paddedStr[i * r + c];
            
            // Output result
            for (int c = 0; c < i; c++)
                for (int r = i - 1; r >= 0; r--)
                    if (nums[r, c] != '*')
                        Console.Write(nums[r, c]);
            
            Console.WriteLine();
        }
    }
}