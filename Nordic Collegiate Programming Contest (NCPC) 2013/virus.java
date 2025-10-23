import java.util.*;

public class virus {

    public static void main(String[] args) {

        Scanner stdin = new Scanner(System.in);
        String s1 = stdin.next();
        String s2 = stdin.next();

        // Greedy match from both sides.
        int i = 0, j = 0;
        while (i < s1.length() && i < s2.length() && s1.charAt(i) == s2.charAt(i)) i++;
        while (j < s1.length() && j < s2.length() && s1.charAt(s1.length()-1-j) == s2.charAt(s2.length()-1-j)) j++;
        j = s2.length() - j;

        // Initial answer is what's left.
        int ans = Math.max(j-i, 0);

        // But, check with lengths of both strings!
        System.out.println(Math.max(ans, s2.length()-s1.length()));
    }
}