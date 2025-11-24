using System;
using System.Collections.Generic;

public struct Point {
    public double x, y;
    
    public Point(double x, double y) {
        this.x = x;
        this.y = y;
    }
}

public class LinearProgramResult {
    public double Value { get; set; }
    public double[] Solution { get; set; }
}

public class Program {
    static double EuclideanDist(Point a, Point b) {
        return Math.Sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    
    static LinearProgramResult LinearProgramSolution(double[][] A, double[] b, double[] c) {
        int m = b.Length;
        int n = c.Length;
        
        double[][] tableau = new double[m + 2][];
        for (int i = 0; i < m + 2; i++) {
            tableau[i] = new double[n + 2];
        }
        
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
        
        void Pivot(int row, int col) {
            double inv = 1.0 / tableau[row][col];
            
            for (int i = 0; i < m + 2; i++) {
                if (i != row && Math.Abs(tableau[i][col]) > 1e-8) {
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
            
            int tempVal = basic[row];
            basic[row] = nonBasic[col];
            nonBasic[col] = tempVal;
        }
        
        bool Simplex(int phase) {
            while (true) {
                int r = m + (phase == 1 ? 1 : 0);
                int col = -1;
                
                for (int j = 0; j <= n; j++) {
                    if (phase == 2 && nonBasic[j] == -1) continue;
                    if (col == -1 || tableau[r][j] < tableau[r][col] - 1e-8 || 
                        (Math.Abs(tableau[r][j] - tableau[r][col]) < 1e-8 && nonBasic[j] < nonBasic[col])) {
                        col = j;
                    }
                }
                
                if (tableau[r][col] >= -1e-8) return true;
                
                int row = -1;
                for (int i = 0; i < m; i++) {
                    if (tableau[i][col] <= 1e-8) continue;
                    if (row == -1 || 
                        tableau[i][n + 1] / tableau[i][col] < tableau[row][n + 1] / tableau[row][col] - 1e-8 ||
                        (Math.Abs(tableau[i][n + 1] / tableau[i][col] - tableau[row][n + 1] / tableau[row][col]) < 1e-8 && 
                         basic[i] < basic[row])) {
                        row = i;
                    }
                }
                
                if (row == -1) return false;
                Pivot(row, col);
            }
        }
        
        int row = 0;
        for (int i = 1; i < m; i++) {
            if (tableau[i][n + 1] < tableau[row][n + 1]) {
                row = i;
            }
        }
        
        if (tableau[row][n + 1] <= -1e-8) {
            Pivot(row, n);
            if (!Simplex(1) || tableau[m + 1][n + 1] < -1e-8) {
                return new LinearProgramResult { Value = double.NegativeInfinity };
            }
            
            for (int i = 0; i < m; i++) {
                if (basic[i] == -1) {
                    int col = -1;
                    for (int j = 0; j <= n; j++) {
                        if (col == -1 || tableau[i][j] < tableau[i][col] - 1e-8 ||
                            (Math.Abs(tableau[i][j] - tableau[i][col]) < 1e-8 && nonBasic[j] < nonBasic[col])) {
                            col = j;
                        }
                    }
                    Pivot(i, col);
                }
            }
        }
        
        if (!Simplex(2)) {
            return new LinearProgramResult { Value = double.PositiveInfinity };
        }
        
        double[] solution = new double[n];
        for (int i = 0; i < m; i++) {
            if (basic[i] < n) {
                solution[basic[i]] = tableau[i][n + 1];
            }
        }
        
        return new LinearProgramResult { 
            Value = tableau[m][n + 1],
            Solution = solution
        };
    }
    
    public static void Main() {
        int n = int.Parse(Console.ReadLine());
        Point[] coords = new Point[n];
        
        for (int i = 0; i < n; i++) {
            string[] parts = Console.ReadLine().Split();
            coords[i] = new Point(double.Parse(parts[0]), double.Parse(parts[1]));
        }
        
        int m = n * (n - 1) / 2;
        double[][] A = new double[m][];
        for (int i = 0; i < m; i++) {
            A[i] = new double[n];
        }
        
        double[] b = new double[m];
        double[] c = new double[n];
        
        for (int i = 0; i < n; i++) {
            c[i] = 1.0;
        }
        
        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                A[k][i] = 1.0;
                A[k][j] = 1.0;
                b[k] = EuclideanDist(coords[i], coords[j]);
                k++;
            }
        }
        
        LinearProgramResult result = LinearProgramSolution(A, b, c);
        Console.WriteLine($"{result.Value:F2}");
    }
}