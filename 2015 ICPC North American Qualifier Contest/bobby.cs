using System;

class Program {
    // Function to compute nCr (n choose r)
    static double Combinations(int n, int k) {
        if (k < 0 || k > n) return 0;
        if (k == 0 || k == n) return 1;
        if (k > n / 2) k = n - k;
        
        double res = 1.0;
        for (int i = 1; i <= k; i++) {
            res = res * (n - i + 1) / i;
        }
        return res;
    }

    static void Main() {
        int N_cases = int.Parse(Console.ReadLine());
        
        for (int i = 0; i < N_cases; i++) {
            string[] input = Console.ReadLine().Split();
            int R = int.Parse(input[0]);
            int S = int.Parse(input[1]);
            int X = int.Parse(input[2]);
            int Y = int.Parse(input[3]);
            int W = int.Parse(input[4]);

            // Calculate probability of a single successful roll
            double p_success = 0.0;
            if (R <= S) {
                p_success = (double)(S - R + 1) / S;
            }

            double p_failure = 1.0 - p_success;

            // Calculate probability of winning the bet
            double P_win = 0.0;
            for (int k = X; k <= Y; k++) {
                double nCk = Combinations(Y, k);
                double p_succ_k = Math.Pow(p_success, k);
                double p_fail_Y_k = Math.Pow(p_failure, Y - k);
                P_win += nCk * p_succ_k * p_fail_Y_k;
            }

            // Calculate expected return and output result
            double E_return = P_win * W;
            if (E_return > 1.0) {
                Console.WriteLine("yes");
            } else {
                Console.WriteLine("no");
            }
        }
    }
}