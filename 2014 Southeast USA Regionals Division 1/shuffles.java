import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;
import java.util.StringTokenizer;

public class shuffles {
    public static void main(String[] args) throws IOException {
        // Use BufferedReader for fast input
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line;

        // The problem statement implies a single test case, but the Kattis environment
        // often tests with multiple cases, so a while loop is safer.
        // However, given the problem's nature, we'll focus on the single case logic
        // and use a try-catch block to handle the input reading.
        
        // Read N
        if ((line = br.readLine()) == null) {
            return;
        }
        int n = Integer.parseInt(line.trim());

        // Read the permutation
        line = br.readLine();
        if (line == null) {
            return;
        }
        StringTokenizer st = new StringTokenizer(line);

        // pos[c] stores the index of card 'c' in the shuffled deck.
        // Card values are 1 to n, so we need size n+1.
        int[] pos = new int[n + 1];
        for (int i = 0; i < n; ++i) {
            int card = Integer.parseInt(st.nextToken());
            pos[card] = i;
        }

        // Core logic: count the number of blocks
        int numBlocks = 0;
        int lastPos = -1; // Position of the last card (card - 1) placed in the current block

        // Iterate through the cards in their original sorted order (1, 2, ..., n)
        for (int card = 1; card <= n; ++card) {
            int currentPos = pos[card];
            
            // If the current card's position is less than the last card's position,
            // it means this card must start a new block.
            if (currentPos < lastPos) {
                numBlocks++;
            }
            lastPos = currentPos;
        }

        // The loop counts the number of times a new block *starts*.
        // The first block is not counted in the loop, so we add 1.
        numBlocks++;

        // The minimum number of shuffles 'k' is the smallest integer such that 2^k >= numBlocks.
        int result = 0;
        int powerOf2 = 1;
        while (powerOf2 < numBlocks) {
            powerOf2 *= 2;
            result++;
        }

        System.out.println(result);
    }
}