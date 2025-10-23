import java.util.Scanner;

public class SnowWhiteDwarves {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read the 9 hat numbers into an array
        int[] hatNumbers = new int[9];
        for (int i = 0; i < 9; i++) {
            hatNumbers[i] = scanner.nextInt();
        }

        // Find the 7 dwarves' hat numbers that sum to 100
        for (int i = 0; i < 9; i++) {
            for (int j = i + 1; j < 9; j++) {
                int sum = 0;
                for (int k = 0; k < 9; k++) {
                    if (k != i && k != j) {
                        sum += hatNumbers[k];
                    }
                }
                if (sum == 100) {
                    // Output the 7 valid hat numbers
                    for (int k = 0; k < 9; k++) {
                        if (k != i && k != j) {
                            System.out.println(hatNumbers[k]);
                        }
                    }
                    return; // Exit the program
                }
            }
        }
    }
}