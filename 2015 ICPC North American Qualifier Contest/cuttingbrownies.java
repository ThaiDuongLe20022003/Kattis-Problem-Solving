import java.util.Scanner;

public class cuttingbrownies {
    static boolean[][] win = new boolean[501][501];
    
    public static void main(String[] args) {
        // Precompute win states
        for (int i = 1; i <= 500; i++) {
            for (int j = 1; j <= 500; j++) {
                win[i][j] = false;
                
                for (int k = 1; k < j; k++) {
                    win[i][j] = win[i][j] || (!win[k][i] && !win[j - k][i]);
                }
            }
        }

        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        for (int i = 0; i < n; i++) {
            int b = scanner.nextInt();
            int d = scanner.nextInt();
            String s = scanner.next();
            
            System.out.print(s + " ");
            if (s.charAt(0) == 'H') {
                System.out.println(win[b][d] ? "can win" : "cannot win");
            } else {
                System.out.println(win[d][b] ? "can win" : "cannot win");
            }
        }
        
        scanner.close();
    }
}