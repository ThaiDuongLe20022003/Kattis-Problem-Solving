using System;
using System.Collections.Generic;

public class Program
{
    class Fence : IComparable<Fence>
    {
        public int Pos { get; set; }
        public int Strength { get; set; }
        public int Idx { get; set; }
        
        public int CompareTo(Fence other)
        {
            return Pos.CompareTo(other.Pos);
        }
    }
    
    public static void Main()
    {
        int n = int.Parse(Console.ReadLine());
        Fence[] fences = new Fence[n];
        int[] l = new int[n];
        int[] r = new int[n];
        
        for (int i = 0; i < n; i++)
        {
            string[] parts = Console.ReadLine().Split();
            fences[i] = new Fence 
            { 
                Pos = int.Parse(parts[0]), 
                Strength = int.Parse(parts[1]),
                Idx = i
            };
            l[i] = i;
            r[i] = i;
        }
        
        Array.Sort(fences);
        
        bool change;
        do
        {
            change = false;
            
            // Forward pass
            Stack<int> stack = new Stack<int>();
            for (int i = 0; i < n; i++)
            {
                while (stack.Count > 0 && 
                       Math.Abs(fences[i].Pos - fences[stack.Peek()].Pos) <= fences[i].Strength)
                {
                    int j = stack.Pop();
                    
                    if (l[i] > l[j])
                    {
                        l[i] = l[j];
                        change = true;
                    }
                    if (r[i] < r[j])
                    {
                        r[i] = r[j];
                        change = true;
                    }
                }
                stack.Push(i);
            }
            
            // Backward pass
            stack = new Stack<int>();
            for (int i = n - 1; i >= 0; i--)
            {
                while (stack.Count > 0 && 
                       Math.Abs(fences[i].Pos - fences[stack.Peek()].Pos) <= fences[i].Strength)
                {
                    int j = stack.Pop();
                    
                    if (l[i] > l[j])
                    {
                        l[i] = l[j];
                        change = true;
                    }
                    if (r[i] < r[j])
                    {
                        r[i] = r[j];
                        change = true;
                    }
                }
                stack.Push(i);
            }
            
        } while (change);
        
        int[] cans = new int[n];
        for (int i = 0; i < n; i++)
        {
            cans[fences[i].Idx] = r[i] - l[i] + 1;
        }
        
        Console.WriteLine(string.Join(" ", cans));
    }
}