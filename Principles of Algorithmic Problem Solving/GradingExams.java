import java.util.Scanner;

public class GradingExams {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read grading limits a, b, c, d, and e
        int a = scanner.nextInt();
        int b = scanner.nextInt();
        int c = scanner.nextInt();
        int d = scanner.nextInt();
        int e = scanner.nextInt();

        // Read the exam score
        int examScore = scanner.nextInt();

        // Determine the grade
        char grade;
        if (100 >= examScore && examScore >= a) {
            grade = 'A';
        } else if (examScore >= b) {
            grade = 'B';
        } else if (examScore >= c) {
            grade = 'C';
        } else if (examScore >= d) {
            grade = 'D';
        } else if (examScore >= e) {
            grade = 'E';
        } else {
            grade = 'F';
        }

        // Print the grade
        System.out.println(grade);
    }
}