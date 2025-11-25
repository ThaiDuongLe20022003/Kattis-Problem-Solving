using System;

public class Program
{
    private static string S;
    private static long[,,,] memo;

    private static long Dp(int pos, int prev_d, bool is_less, bool is_started, bool is_falling)
    {
        if (pos == S.Length)
        {
            return is_started ? 1 : 0;
        }
        
        int less = is_less ? 1 : 0;
        int falling = is_falling ? 1 : 0;
        
        if (memo[pos, prev_d, less, falling] != -1)
        {
            return memo[pos, prev_d, less, falling];
        }

        long ans = 0;
        int upper_bound = is_less ? 9 : (S[pos] - '0');

        for (int d = 0; d <= upper_bound; d++)
        {
            if (!is_started)
            {
                if (d == 0)
                {
                    ans += Dp(pos + 1, 0, true, false, false);
                }
                else
                {
                    ans += Dp(pos + 1, d, is_less || (d < upper_bound), true, false);
                }
            }
            else
            {
                if (is_falling)
                {
                    if (d <= prev_d)
                    {
                        ans += Dp(pos + 1, d, is_less || (d < upper_bound), true, true);
                    }
                }
                else
                {
                    if (d < prev_d)
                    {
                        ans += Dp(pos + 1, d, is_less || (d < upper_bound), true, true);
                    }
                    else
                    {
                        ans += Dp(pos + 1, d, is_less || (d < upper_bound), true, false);
                    }
                }
            }
        }

        memo[pos, prev_d, less, falling] = ans;
        return ans;
    }

    private static bool IsHillNumber(string s)
    {
        if (string.IsNullOrEmpty(s)) return false;
        if (s.Trim('0') == "") return false;

        bool falling = false;
        for (int i = 0; i < s.Length - 1; i++)
        {
            if (s[i] < s[i + 1])
            {
                if (falling) return false;
            }
            else if (s[i] > s[i + 1])
            {
                falling = true;
            }
        }
        return true;
    }

    private static long Solve(string n_str)
    {
        S = n_str;
        memo = new long[20, 10, 2, 2];
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 2; k++)
                    for (int l = 0; l < 2; l++)
                        memo[i, j, k, l] = -1;
                        
        return Dp(0, 0, false, false, false);
    }

    public static void Main()
    {
        string n_str;
        while ((n_str = Console.ReadLine()) != null && n_str != "")
        {
            if (!IsHillNumber(n_str))
            {
                Console.WriteLine("-1");
            }
            else
            {
                Console.WriteLine(Solve(n_str));
            }
        }
    }
}