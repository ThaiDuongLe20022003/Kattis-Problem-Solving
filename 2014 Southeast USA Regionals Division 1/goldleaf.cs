using System;
using System.Collections.Generic;

public class Program
{
    class Tuple : IComparable<Tuple>
    {
        public int r1, c1, r2, c2;
        
        public Tuple(int r1, int c1, int r2, int c2)
        {
            this.r1 = r1;
            this.c1 = c1;
            this.r2 = r2;
            this.c2 = c2;
        }
        
        public int CompareTo(Tuple other)
        {
            if (r1 != other.r1) return r1.CompareTo(other.r1);
            if (c1 != other.c1) return c1.CompareTo(other.c1);
            if (r2 != other.r2) return r2.CompareTo(other.r2);
            return c2.CompareTo(other.c2);
        }
    }
    
    static bool ValidVert(int r1, int c1, int r2, int c2, int n, int m, string[] grid)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int i1 = i;
                int j1 = 2 * c1 - j + 1;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m)
                {
                    if (grid[i][j] == '.')
                        return false;
                    else
                        continue;
                }
                if (grid[i][j] == grid[i1][j1])
                    return false;
            }
        }
        return true;
    }
    
    static void GetVert(int n, int m, string[] grid, SortedSet<Tuple> rv)
    {
        for (int i = 0; i < m; i++)
        {
            int r1 = 0, c1 = i, r2 = n - 1, c2 = i;
            if (ValidVert(r1, c1, r2, c2, n, m, grid))
            {
                rv.Add(new Tuple(r1, c1, r2, c2));
                return;
            }
        }
    }
    
    static bool ValidHor(int r1, int c1, int r2, int c2, int n, int m, string[] grid)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int i1 = 2 * r1 - i + 1, j1 = j;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m)
                {
                    if (grid[i][j] == '.')
                        return false;
                    else
                        continue;
                }
                if (grid[i][j] == grid[i1][j1])
                    return false;
            }
        }
        return true;
    }
    
    static void GetHor(int n, int m, string[] grid, SortedSet<Tuple> rv)
    {
        for (int i = 0; i < n; i++)
        {
            int r1 = i, c1 = 0, r2 = i, c2 = m - 1;
            if (ValidHor(r1, c1, r2, c2, n, m, grid))
            {
                rv.Add(new Tuple(r1, c1, r2, c2));
                return;
            }
        }
    }
    
    static bool ValidDiag1(int r1, int c1, int r2, int c2, int n, int m, string[] grid)
    {
        int s = r1 + c1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int i1 = s - j, j1 = s - i;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m)
                {
                    if (grid[i][j] == '.')
                        return false;
                    else
                        continue;
                }
                if (i == i1 && j == j1)
                {
                    if (grid[i][j] == '.')
                        return false;
                    else
                        continue;
                }
                if (grid[i][j] == grid[i1][j1])
                    return false;
            }
        }
        return true;
    }
    
    static void GetDiag1(int n, int m, string[] grid, SortedSet<Tuple> rv)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (j != 0 && i != n - 1)
                    continue;
                    
                int r1 = i, c1 = j, r2 = i, c2 = j;
                while (r2 >= 0 && c2 < m)
                {
                    r2--; c2++;
                }
                r2++; c2--;
                if (ValidDiag1(r1, c1, r2, c2, n, m, grid))
                {
                    rv.Add(new Tuple(r1, c1, r2, c2));
                    return;
                }
            }
        }
    }
    
    static bool ValidDiag2(int r1, int c1, int r2, int c2, int n, int m, string[] grid)
    {
        int s = r1 - c1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int i1 = s + j, j1 = i - s;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m)
                {
                    if (grid[i][j] == '.')
                        return false;
                    else
                        continue;
                }
                if (i == i1 && j == j1)
                {
                    if (grid[i][j] == '.')
                        return false;
                    else
                        continue;
                }
                if (grid[i][j] == grid[i1][j1])
                    return false;
            }
        }
        return true;
    }
    
    static void GetDiag2(int n, int m, string[] grid, SortedSet<Tuple> rv)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (j != 0 && i != 0)
                    continue;
                    
                int r1 = i, c1 = j, r2 = i, c2 = j;
                while (r2 < n && c2 < m)
                {
                    r2++; c2++;
                }
                r2--; c2--;
                if (ValidDiag2(r1, c1, r2, c2, n, m, grid))
                {
                    rv.Add(new Tuple(r1, c1, r2, c2));
                    return;
                }
            }
        }
    }
    
    public static void Main()
    {
        string[] input = Console.ReadLine().Split();
        int n = int.Parse(input[0]);
        int m = int.Parse(input[1]);
        
        string[] grid = new string[n];
        for (int i = 0; i < n; i++)
        {
            grid[i] = Console.ReadLine();
        }
        
        SortedSet<Tuple> rv = new SortedSet<Tuple>();
        GetVert(n, m, grid, rv);
        GetHor(n, m, grid, rv);
        GetDiag1(n, m, grid, rv);
        GetDiag2(n, m, grid, rv);
        
        if (rv.Count > 0)
        {
            Tuple first = rv.Min;
            Console.WriteLine($"{first.r1 + 1} {first.c1 + 1} {first.r2 + 1} {first.c2 + 1}");
        }
    }
}