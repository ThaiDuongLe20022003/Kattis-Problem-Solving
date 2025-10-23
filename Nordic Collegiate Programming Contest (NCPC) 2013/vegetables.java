import java.util.*;

public class vegetables {

    public static int[] values;
    public static int n;
    public static double ratio;

    public static void main(String[] args) {

        // Read in data.
        Scanner stdin = new Scanner(System.in);
        ratio = stdin.nextDouble();
        n = stdin.nextInt();

        values = new int[n];
        for (int i=0; i<n; i++)
            values[i] = stdin.nextInt();

        // Easy to sort from low to high.
        Arrays.sort(values);

        // Return first solution we find, since we are searching from low to high.
        System.out.println(solve(0, values[0], values[0], 0));
    }

    // Currently cutting the vegetable values[k] and our current min, max and cuts are passed in.
    public static int solve(int k, double curMin, double curMax, int curCuts) {

        // Here is our answer.
        if (k == n)
            return curCuts;

        // Possible number of cuts for this vegetable.
        double absMax = curMin/ratio;
        double absMin = curMax*ratio;
        int low = (int)Math.ceil(values[k]/absMax);
        int high = (int)(values[k]/absMin);

        // Special case when we start search.
        if (k == 0) {
            low = 1;
            high = values[0];
        }

        // Try i-1 cuts.
        for (int i=low; i<=high; i++) {
            double newL = values[k]/i;

            // Set these for the first iteration.
            if (k == 0) curMin = newL;
            if (k == 0) curMax = newL;

            // See if this arrangement works, if it does, return it.
            int ans = solve(k+1, Math.min(curMin, newL), Math.max(curMax, newL), curCuts+i-1);
            if (ans != -1)
                return ans;
        }

        // Nothing worked.
        return -1;
    }
}