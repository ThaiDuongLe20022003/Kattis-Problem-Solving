import java.util.*;

public class timebomb {

    // Stores fixed values, 1='*', 0 =' '
    final public static int[][] CODES = {{7,5,5,5,7},{1,1,1,1,1},{7,1,7,4,7},{7,1,7,1,7},{5,5,7,1,1},
                                         {7,4,7,1,7},{7,4,7,5,7},{7,1,1,1,1},{7,5,7,5,7},{7,5,7,1,7}};

    final public static int INVALID = -1;

    public static void main(String[] args) {

        Scanner stdin = new Scanner(System.in);

        // Read input.
        String[] input = new String[5];
        for (int i=0; i<5; i++)
            input[i] = stdin.nextLine();

        // Output solution.
        System.out.println(solve(input));
    }

    public static String solve(String[] input) {

        // Convert to grid and get number.
        int[][] grid = convert(input);
        int value = getNum(grid);

        // Return result.
        if (value%6 == 0)
            return "BEER!!";
        return "BOOM!!";
    }

    // Converts to integer grid, 1 for '*', 0 for ' '.
    public static int[][] convert(String[] input) {
        int[][] ans = new int[5][input[0].length()];
        for (int i=0; i<input.length; i++)
            for (int j=0; j<input[i].length(); j++)
                if (input[i].charAt(j) == '*')
                    ans[i][j] = 1;
        return ans;
    }

    // Returns the integer value of this text number, -1 if invalid.
    public static int getNum(int[][] grid) {

        int ans = 0;

        // Loop through each digit.
        for (int i=0; i<grid[0].length; i+=4) {

            // Get this digit.
            int[] item = new int[5];
            for (int j=0; j<grid.length; j++)
                item[j] = convert(grid[j], i);

            // Find which digit it is.
            int value = getVal(item);
            if (value == INVALID) return INVALID;

            // Process this digit.
            ans = 10*ans + value;
        }

        // Final answer.
        return ans;
    }

    // Returns numeric value of the spot in this row of the grid, starting at index pos.
    public static int convert(int[] row, int pos) {
        return row[pos]*4 + row[pos+1]*2 + row[pos+2];
    }

    // Returns which digit is encoded by item, if any, or -1 otherwise.
    public static int getVal(int[] item) {

        // Try each digit to match.
        for (int guess=0; guess<10; guess++) {

            boolean flag = true;

            // Look for mismatch.
            for (int i=0; i<5; i++)
                if (CODES[guess][i] != item[i])
                    flag = false;

            // If flag is still true, we have a match!
            if (flag) return guess;
        }

        // Never found one.
        return INVALID;
    }
}