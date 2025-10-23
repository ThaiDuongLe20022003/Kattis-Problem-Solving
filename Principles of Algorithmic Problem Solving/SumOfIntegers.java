import java.util.Scanner;

public class SumOfIntegers {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read the number of integers (N)
        int N = scanner.nextInt();

        // Initialize a variable to store the sum
        int sum = 0;

        // Read and sum the N integers
        for (int i = 0; i < N; i++) {
            int num = scanner.nextInt();
            sum += num;
        }

        // Print the sum
        System.out.println(sum);
    }
}