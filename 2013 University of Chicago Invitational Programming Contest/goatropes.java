import java.util.*;

class Point {
    double x, y;
    
    Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
}

class LinearProgramResult {
    double value;
    double[] solution;
}

public class goatropes {
    static double euclideanDist(Point a, Point b) {
        return Math.sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    
    static LinearProgramResult linearProgramSolution(double[][] A, double[] b, double[] c) {
        int m = b.length;
        int n = c.length;
        
        double[][] tableau = new double[m + 2][n + 2];
        int[] basic = new int[m];
        int[] nonBasic = new int[n + 1];
        
        // Initialize tableau
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                tableau[i][j] = A[i][j];
            }
            basic[i] = n + i;
            tableau[i][n] = -1;
            tableau[i][n + 1] = b[i];
        }
        
        for (int j = 0; j <= n; j++) {
            nonBasic[j] = j;
        }
        nonBasic[n] = -1;
        
        for (int j = 0; j < n; j++) {
            tableau[m][j] = -c[j];
        }
        tableau[m + 1][n] = 1;
        
        LinearProgramResult result = new LinearProgramResult();
        
        class SimplexSolver {
            void pivot(int row, int col) {
                double inv = 1.0 / tableau[row][col];
                
                for (int i = 0; i < m + 2; i++) {
                    if (i != row && Math.abs(tableau[i][col]) > 1e-8) {
                        double temp = tableau[i][col] * inv;
                        for (int j = 0; j < n + 2; j++) {
                            tableau[i][j] -= tableau[row][j] * temp;
                        }
                        tableau[i][col] = tableau[row][col] * temp;
                    }
                }
                
                for (int i = 0; i < m + 2; i++) {
                    if (i != row) {
                        tableau[i][col] *= -inv;
                    }
                }
                
                for (int j = 0; j < n + 2; j++) {
                    if (j != col) {
                        tableau[row][j] *= inv;
                    }
                }
                tableau[row][col] = inv;
                
                int temp = basic[row];
                basic[row] = nonBasic[col];
                nonBasic[col] = temp;
            }
            
            boolean simplex(int phase) {
                while (true) {
                    int r = m + (phase == 1 ? 1 : 0);
                    int col = -1;
                    
                    for (int j = 0; j <= n; j++) {
                        if (phase == 2 && nonBasic[j] == -1) continue;
                        if (col == -1 || tableau[r][j] < tableau[r][col] - 1e-8 || 
                            (Math.abs(tableau[r][j] - tableau[r][col]) < 1e-8 && nonBasic[j] < nonBasic[col])) {
                            col = j;
                        }
                    }
                    
                    if (tableau[r][col] >= -1e-8) return true;
                    
                    int row = -1;
                    for (int i = 0; i < m; i++) {
                        if (tableau[i][col] <= 1e-8) continue;
                        if (row == -1 || 
                            tableau[i][n + 1] / tableau[i][col] < tableau[row][n + 1] / tableau[row][col] - 1e-8 ||
                            (Math.abs(tableau[i][n + 1] / tableau[i][col] - tableau[row][n + 1] / tableau[row][col]) < 1e-8 && 
                             basic[i] < basic[row])) {
                            row = i;
                        }
                    }
                    
                    if (row == -1) return false;
                    pivot(row, col);
                }
            }
        }
        
        SimplexSolver solver = new SimplexSolver();
        
        int row = 0;
        for (int i = 1; i < m; i++) {
            if (tableau[i][n + 1] < tableau[row][n + 1]) {
                row = i;
            }
        }
        
        if (tableau[row][n + 1] <= -1e-8) {
            solver.pivot(row, n);
            if (!solver.simplex(1) || tableau[m + 1][n + 1] < -1e-8) {
                result.value = Double.NEGATIVE_INFINITY;
                return result;
            }
            
            for (int i = 0; i < m; i++) {
                if (basic[i] == -1) {
                    int col = -1;
                    for (int j = 0; j <= n; j++) {
                        if (col == -1 || tableau[i][j] < tableau[i][col] - 1e-8 ||
                            (Math.abs(tableau[i][j] - tableau[i][col]) < 1e-8 && nonBasic[j] < nonBasic[col])) {
                            col = j;
                        }
                    }
                    solver.pivot(i, col);
                }
            }
        }
        
        if (!solver.simplex(2)) {
            result.value = Double.POSITIVE_INFINITY;
            return result;
        }
        
        double[] solution = new double[n];
        for (int i = 0; i < m; i++) {
            if (basic[i] < n) {
                solution[basic[i]] = tableau[i][n + 1];
            }
        }
        
        result.value = tableau[m][n + 1];
        result.solution = solution;
        return result;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        Point[] coords = new Point[n];
        
        for (int i = 0; i < n; i++) {
            coords[i] = new Point(scanner.nextDouble(), scanner.nextDouble());
        }
        
        int m = n * (n - 1) / 2;
        double[][] A = new double[m][n];
        double[] b = new double[m];
        double[] c = new double[n];
        
        Arrays.fill(c, 1.0);
        
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                A[k][i] = 1.0;
                A[k][j] = 1.0;
                b[k] = euclideanDist(coords[i], coords[j]);
                k++;
            }
        }
        
        LinearProgramResult result = linearProgramSolution(A, b, c);
        System.out.printf("%.2f\n", result.value);
        
        scanner.close();
    }
}