import java.util.*;

public class plot {
    static class Binomial {
        private static List<List<Integer>> mem = new ArrayList<>();
        static {
            mem.add(Arrays.asList(1));
        }
        
        public static int coefficient(int n, int k) {
            while (mem.size() <= n) {
                int last = mem.size() - 1;
                List<Integer> newRow = new ArrayList<>();
                newRow.add(1);
                for (int j = 1; j < mem.size(); j++) {
                    newRow.add(mem.get(last).get(j - 1) + mem.get(last).get(j));
                }
                newRow.add(1);
                mem.add(newRow);
            }
            return mem.get(n).get(k);
        }
    }
    
    static class Polynomial {
        private double[] a;
        private double[] points;
        
        public Polynomial(double[] coefficients, int n) {
            a = coefficients;
            points = new double[n + 1];
            for (int x = 0; x <= n; x++) {
                points[x] = evalAt(x);
            }
        }
        
        private double evalAt(int x) {
            if (x == 0) return a[0];
            double result = 0.0;
            double power = 1.0;
            for (double coeff : a) {
                result += coeff * power;
                power *= x;
            }
            return result;
        }
        
        public double get(int x) {
            return points[x];
        }
    }
    
    public static double[] findC(int n, double[] a) {
        Polynomial p = new Polynomial(a, n);
        List<Double> c = new ArrayList<>();
        c.add(p.get(0));
        
        for (int i = 0; i < n; i++) {
            double sum = p.get(i + 1) - p.get(i);
            for (int j = 0; j < i; j++) {
                sum -= Binomial.coefficient(i, j) * c.get(j + 1);
            }
            c.add(sum);
        }
        
        double[] result = new double[c.size()];
        for (int i = 0; i < c.size(); i++) {
            result[i] = c.get(i);
        }
        return result;
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        double[] a = new double[n + 1];
        for (int i = 0; i <= n; i++) {
            a[i] = scanner.nextDouble();
        }
        
        // Reverse the array
        for (int i = 0; i <= n / 2; i++) {
            double temp = a[i];
            a[i] = a[n - i];
            a[n - i] = temp;
        }
        
        double[] c = findC(n, a);
        
        for (double val : c) {
            System.out.print((int) val + " ");
        }
        System.out.println();
        
        scanner.close();
    }
}