using System;

public class Program
{
    public static void Main()
    {
        string[] inputs = Console.ReadLine().Split(' ');
        double a = double.Parse(inputs[0]);
        double b = double.Parse(inputs[1]);
        double c = double.Parse(inputs[2]);

        double s = (a + b + c) / 2;
        double area = Math.Sqrt(s * (s - a) * (s - b) * (s - c));
        double t = a * a + b * b + c * c;
        double carpet = (Math.Sqrt(3) / 4 * t + 3 * area) / 2;
        
        bool validTriangle = (a + b >= c && a + c >= b && b + c >= a);
        double minSide = Math.Sqrt(carpet * 4 / Math.Sqrt(3));
        double maxSide = Math.Max(a, Math.Max(b, c));
        bool meetsCondition = (minSide >= maxSide);
        
        if (validTriangle && meetsCondition)
        {
            Console.WriteLine($"{carpet:F3}");
        }
        else
        {
            Console.WriteLine("-1");
        }
    }
}