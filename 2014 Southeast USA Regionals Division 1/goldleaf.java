import java.util.*;

public class goldleaf {
    static class Tuple implements Comparable<Tuple> {
        int r1, c1, r2, c2;
        
        Tuple(int r1, int c1, int r2, int c2) {
            this.r1 = r1;
            this.c1 = c1;
            this.r2 = r2;
            this.c2 = c2;
        }
        
        @Override
        public int compareTo(Tuple other) {
            if (r1 != other.r1) return Integer.compare(r1, other.r1);
            if (c1 != other.c1) return Integer.compare(c1, other.c1);
            if (r2 != other.r2) return Integer.compare(r2, other.r2);
            return Integer.compare(c2, other.c2);
        }
    }
    
    static boolean validVert(int r1, int c1, int r2, int c2, int n, int m, char[][] grid) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int i1 = i;
                int j1 = 2 * c1 - j + 1;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                    if (grid[i][j] == '.') {
                        return false;
                    } else {
                        continue;
                    }
                }
                if (grid[i][j] == grid[i1][j1]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    static void getVert(int n, int m, char[][] grid, TreeSet<Tuple> rv) {
        for (int i = 0; i < m; i++) {
            int r1 = 0, c1 = i, r2 = n - 1, c2 = i;
            if (validVert(r1, c1, r2, c2, n, m, grid)) {
                rv.add(new Tuple(r1, c1, r2, c2));
                return;
            }
        }
    }
    
    static boolean validHor(int r1, int c1, int r2, int c2, int n, int m, char[][] grid) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int i1 = 2 * r1 - i + 1, j1 = j;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                    if (grid[i][j] == '.') {
                        return false;
                    } else {
                        continue;
                    }
                }
                if (grid[i][j] == grid[i1][j1]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    static void getHor(int n, int m, char[][] grid, TreeSet<Tuple> rv) {
        for (int i = 0; i < n; i++) {
            int r1 = i, c1 = 0, r2 = i, c2 = m - 1;
            if (validHor(r1, c1, r2, c2, n, m, grid)) {
                rv.add(new Tuple(r1, c1, r2, c2));
                return;
            }
        }
    }
    
    static boolean validDiag1(int r1, int c1, int r2, int c2, int n, int m, char[][] grid) {
        int s = r1 + c1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int i1 = s - j, j1 = s - i;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                    if (grid[i][j] == '.') {
                        return false;
                    } else {
                        continue;
                    }
                }
                if (i == i1 && j == j1) {
                    if (grid[i][j] == '.') {
                        return false;
                    } else {
                        continue;
                    }
                }
                if (grid[i][j] == grid[i1][j1]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    static void getDiag1(int n, int m, char[][] grid, TreeSet<Tuple> rv) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j != 0 && i != n - 1) {
                    continue;
                }
                int r1 = i, c1 = j, r2 = i, c2 = j;
                while (r2 >= 0 && c2 < m) {
                    r2--; c2++;
                }
                r2++; c2--;
                if (validDiag1(r1, c1, r2, c2, n, m, grid)) {
                    rv.add(new Tuple(r1, c1, r2, c2));
                    return;
                }
            }
        }
    }
    
    static boolean validDiag2(int r1, int c1, int r2, int c2, int n, int m, char[][] grid) {
        int s = r1 - c1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int i1 = s + j, j1 = i - s;
                if (i1 < 0 || i1 >= n || j1 < 0 || j1 >= m) {
                    if (grid[i][j] == '.') {
                        return false;
                    } else {
                        continue;
                    }
                }
                if (i == i1 && j == j1) {
                    if (grid[i][j] == '.') {
                        return false;
                    } else {
                        continue;
                    }
                }
                if (grid[i][j] == grid[i1][j1]) {
                    return false;
                }
            }
        }
        return true;
    }
    
    static void getDiag2(int n, int m, char[][] grid, TreeSet<Tuple> rv) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j != 0 && i != 0) {
                    continue;
                }
                int r1 = i, c1 = j, r2 = i, c2 = j;
                while (r2 < n && c2 < m) {
                    r2++; c2++;
                }
                r2--; c2--;
                if (validDiag2(r1, c1, r2, c2, n, m, grid)) {
                    rv.add(new Tuple(r1, c1, r2, c2));
                    return;
                }
            }
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        char[][] grid = new char[n][m];
        for (int i = 0; i < n; i++) {
            String line = scanner.nextLine();
            grid[i] = line.toCharArray();
        }
        
        TreeSet<Tuple> rv = new TreeSet<>();
        getVert(n, m, grid, rv);
        getHor(n, m, grid, rv);
        getDiag1(n, m, grid, rv);
        getDiag2(n, m, grid, rv);
        
        if (!rv.isEmpty()) {
            Tuple first = rv.first();
            System.out.println((first.r1 + 1) + " " + (first.c1 + 1) + " " + 
                             (first.r2 + 1) + " " + (first.c2 + 1));
        }
    }
}