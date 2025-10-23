import java.util.Scanner;

public class SmallestHarshadNumber {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        scanner.close();

        int result = findSmallestHarshadNumber(n);
        System.out.println(result);
    }

    public static int findSmallestHarshadNumber(int n) {
        while (true) {
            if (isHarshadNumber(n)) {
                return n;
            }
            n++;
        }
    }

    public static boolean isHarshadNumber(int num) {
        int originalNum = num;
        int digitSum = 0;

        // Calculate the sum of the digits
        while (num > 0) {
            digitSum += num % 10;
            num /= 10;
        }

        // Check if the number is divisible by its digit sum
        return originalNum % digitSum == 0;
    }
}