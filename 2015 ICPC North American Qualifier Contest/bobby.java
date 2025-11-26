import java.util.Scanner;

public class bobby {
    // Function to compute nCr (n choose r)
    static double combinations(int n, int k) {
        if (k < 0 || k > n) return 0;
        if (k == 0 || k == n) return 1;
        if (k > n / 2) k = n - k;
        
        double res = 1.0;
        for (int i = 1; i <= k; i++) {
            res = res * (n - i + 1) / i;
        }
        return res;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N_cases = scanner.nextInt();
        
        for (int i = 0; i < N_cases; i++) {
            int R = scanner.nextInt();
            int S = scanner.nextInt();
            int X = scanner.nextInt();
            int Y = scanner.nextInt();
            int W = scanner.nextInt();

            // Calculate probability of a single successful roll
            double p_success = 0.0;
            if (R <= S) {
                p_success = (double)(S - R + 1) / S;
            }

            double p_failure = 1.0 - p_success;

            // Calculate probability of winning the bet
            double P_win = 0.0;
            for (int k = X; k <= Y; k++) {
                double nCk = combinations(Y, k);
                double p_succ_k = Math.pow(p_success, k);
                double p_fail_Y_k = Math.pow(p_failure, Y - k);
                P_win += nCk * p_succ_k * p_fail_Y_k;
            }

            // Calculate expected return and output result
            double E_return = P_win * W;
            if (E_return > 1.0) {
                System.out.println("yes");
            } else {
                System.out.println("no");
            }
        }
        
        scanner.close();
    }
}