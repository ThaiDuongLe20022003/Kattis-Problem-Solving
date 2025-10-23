import java.util.Scanner;

public class StoneGame {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read the number of stones (N)
        int N = scanner.nextInt();

        // Determine the winner
        String winner = (N % 2 == 1) ? "Alice" : "Bob";

        // Print the winner
        System.out.println(winner);
    }
}