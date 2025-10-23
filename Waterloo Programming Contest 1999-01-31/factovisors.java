import java.io.*;
import java.util.*;

class factovisors {
    BufferedReader in;
    int prime[], pow[], len;
    int valval[][];
    int max = (int) Math.pow(1.0 * ((long) Math.pow(2, 31)), 0.5) + 10;

    public factovisors() throws IOException {
        in = new BufferedReader(new InputStreamReader(System.in));

        primes();
        String s;
        while ((s = in.readLine()) != null && !s.isEmpty()) {
            String[] ss = s.split(" ");
            int n = Integer.valueOf(ss[0]);
            int m = Integer.valueOf(ss[1]);

            int mm = m;
            if (m == 0) {
                System.out.println(mm + " does not divide " + n + "!");
                continue;
            }
            if (m == 1) {
                System.out.println(mm + " divides " + n + "!");
                continue;
            }
            if (n == 0 || n == 1) {
                System.out.println(mm + " does not divide " + n + "!");
                continue;
            }
            boolean flag = true;
            int st = (int) Math.pow(m, 0.5);

            for (int i = 0; prime[i] <= st; i++) {
                int cnt;
                for (cnt = 0; m % prime[i] == 0; cnt++)
                    m /= prime[i];
                pow[i] = cnt;

                if (pow[i] == 0)
                    continue;
                int req = valval[i][pow[i] - 1];
                if (req > n) {
                    flag = false;
                    break;
                }
                if (m == 1)
                    break;
            }
            if (flag) {
                if (m == 1 || m <= n) {
                    System.out.println(mm + " divides " + n + "!");
                    continue;
                }
            }
            System.out.println(mm + " does not divide " + n + "!");
        }
        in.close();
    }

    void primes() {
        prime = new int[max];
        pow = new int[max];
        len = 0;
        boolean flag[] = new boolean[max];
        Arrays.fill(flag, true);
        for (int i = 2; i < max; i++) {
            if (!flag[i])
                continue;
            prime[len++] = i;
            for (int j = i; (long) i * j < max; j++)
                flag[i * j] = false;
        }
        fill1();
    }

    void fill1() {
        valval = new int[len][];
        for (int i = 0; i < len; i++) {
            int now = (int) (Math.log(Math.pow(2, 31) - 1) / Math.log(prime[i]));
            valval[i] = new int[now];
            int j = 0;
            for (int k = prime[i]; j < now; k += prime[i]) {
                for (int l = k; l % prime[i] == 0 && j < now; l /= prime[i])
                    valval[i][j++] = k;
            }
        }
    }

    public static void main(String args[]) throws IOException {
        new factovisors();
    }
}