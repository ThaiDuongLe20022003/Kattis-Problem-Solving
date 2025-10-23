import java.util.*;

public class erase {

    public static void main(String[] args) {

        Scanner stdin = new Scanner(System.in);
        int n = stdin.nextInt();
        String s1 = stdin.next();
        String s2 = stdin.next();

        // Conditions for success - equal or opposite strings, depending on n.
        if ((n%2 == 0 && s1.equals(s2)) || (n%2 == 1 && s1.equals(flip(s2))))
            System.out.println("Deletion succeeded");
        else
            System.out.println("Deletion failed");
    }

    // Returns s' such that s xor s' is all 1s.
    public static String flip(String s) {
        String ans = "";
        for (int i=0; i<s.length(); i++)
            if (s.charAt(i) == '0')
                ans = ans + "1";
            else
                ans = ans + "0";
        return ans;
    }
}