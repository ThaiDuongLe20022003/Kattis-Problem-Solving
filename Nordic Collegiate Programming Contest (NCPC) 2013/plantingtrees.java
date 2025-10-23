import java.util.*;

public class plantingtrees {

    public static void main(String[] args) {

        // Read data.
        Scanner stdin = new Scanner(System.in);
        int n = stdin.nextInt();
        int[] vals = new int[n];
        for (int i=0; i<n; i++)
            vals[i] = stdin.nextInt();

        // Sort and reverse - greedy (plant slowest trees first).
        Arrays.sort(vals);
        for (int i=0; i<n/2; i++) {
            int temp = vals[i];
            vals[i] = vals[n-1-i];
            vals[n-1-i] = temp;
        }

        // Try each tree and pick the longest one.
        int ans = vals[0] + 2;
        for (int i=1; i<n; i++) {
            if (i+2+vals[i] > ans)
                ans = i+2+vals[i];
        }

        // Print result.
        System.out.println(ans);
    }
}