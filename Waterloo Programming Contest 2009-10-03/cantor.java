import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.TreeSet;

class cantor {
    static final double pi = 4.0 * Math.atan(1.0);
    static final int iinf = 1_000_000_010;
    static final long inf = 1_000_000_000_000_000_010L;
    static final int mod = 1_000_000_007;
    static final double prec = 0.000001;

    public static void main(String[] args) throws IOException {

        FastScanner sc = new FastScanner();

        String s;
        while (!(s = sc.next()).equals("END")) {
            if (s.equals("0") || s.equals("1")) {
                System.out.println("MEMBER");
            } else {
                while (s.charAt(0) != '.') {
                    s = s.substring(1);
                }
                if (works(conv(s))) {
                    System.out.println("MEMBER");
                } else {
                    System.out.println("NON-MEMBER");
                }
            }
        }
    }

    static int conv(String s) {
        int val = 0;
        for (int i = 1; i <= 6; i++) {
            val *= 10;
            if (i < s.length()) {
                val += s.charAt(i) - '0';
            }
        }
        return val;
    }

    static boolean works(int n) {
        Set<Integer> seen = new HashSet<>();
        while (!seen.contains(n)) {
            seen.add(n);
            n *= 3;
            if (n / 1_000_000 == 1) {
                return false;
            }
            n %= 1_000_000;
        }
        return true;
    }

    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;

        public FastScanner() {
            br = new BufferedReader(new InputStreamReader(System.in));
        }

        String next() throws IOException {
            while (st == null || !st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
            }
            return st.nextToken();
        }

        int nextInt() throws IOException {
            return Integer.parseInt(next());
        }

        long nextLong() throws IOException {
            return Long.parseLong(next());
        }

        double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }
    }
}