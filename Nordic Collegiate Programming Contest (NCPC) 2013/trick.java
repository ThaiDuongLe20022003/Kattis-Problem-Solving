import java.util.*;

public class trick {

    public static void main(String[] args) {

        Scanner stdin = new Scanner(System.in);
        double ratio = stdin.nextDouble();

        // Easy no solution case.
        if (ratio > 10)
            System.out.println("No solution");

        // Typical case.
        else {

            // Store answers here.
            ArrayList<Long> list = new ArrayList<Long>();

            // Store ratio as an integer, so this is 10^4 times ratio.
            long ratio10000 = (long)(ratio*10000+1e-8);

            // Loop through all 1-8 digit numbers, of the form digit*10^exp + val
            for (int exp=0; exp<8; exp++) {
                for (int digit=1; digit<10; digit++) {

                    // This fraction must be an integer for there to be a solution.
                    long num = (ratio10000*digit*mypow(10L,exp)-digit*mypow(10L,4));
                    long den = 100000L - ratio10000;

                    // Avoid divide by zero...otherwise, we have a solution iff the fraction is an int.
                    if (den != 0 && num%den == 0) {
                        long oldval = digit*mypow(10L, exp) + num/den;
                        long newval = 10*num/den + digit;
                        if (Math.abs(oldval*ratio-newval) < 1 && num/den < mypow(10L, exp))
                            list.add(digit*mypow(10,exp)+num/den);
                    }
                }
            }

            // Nothing worked.
            if (list.size() == 0)
                System.out.println("No solution");

            // Print out everything that did work, sorted.
            else {
                Collections.sort(list);
                for (int i=0; i<list.size(); i++)
                    System.out.println(list.get(i));
            }
        }
    }

    // Returns b^e.
    public static long mypow(long b, int e) {
        long ans = 1;
        for (int i=0; i<e; i++)
            ans = ans*b;
        return ans;
    }
}