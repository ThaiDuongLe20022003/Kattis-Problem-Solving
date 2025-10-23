import java.util.Scanner;
import java.lang.Math;
import java.math.RoundingMode;
import java.text.DecimalFormat;

public class LadderLength {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int h = scanner.nextInt(); // Height of the wall in centimeters
        int v = scanner.nextInt(); // Maximum angle in degrees

        // Convert the angle from degrees to radians
        double angleInRadians = Math.toRadians(v);

        // Calculate the minimum ladder length using trigonometry (sin)
        double ladderLength = h / Math.sin(angleInRadians);

        // Round up to the nearest integer
        int roundedLadderLength = (int) Math.ceil(ladderLength);

        System.out.println(roundedLadderLength);
    }
}