import java.util.Scanner;

public class PerfectNumbers {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (scanner.hasNext()) {
            int num = scanner.nextInt();
            String result = checkPerfectness(num);
            System.out.println(num + " " + result);
        }
    }

    // Function to check if a number is perfect, almost perfect, or not perfect
    static String checkPerfectness(int num) {
        int divisorSum = 1; // Start with 1 since it is always a divisor

        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                divisorSum += i;
                if (i != num / i) {
                    divisorSum += num / i;
                }
            }
        }

        if (divisorSum == num) {
            return "perfect";
        } else if (Math.abs(divisorSum - num) <= 2) {
            return "almost perfect";
        } else {
            return "not perfect";
        }
    }
}