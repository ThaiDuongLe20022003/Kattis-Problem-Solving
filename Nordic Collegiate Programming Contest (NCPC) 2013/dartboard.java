import java.util.*;

public class dartboard {

    public static double var;

    // Precompute expectations for each area of the dartboard here.
    final static double[] expPts = {50, 25, 10.5, 31.5, 10.5, 21};

    public static void main(String[] args) {

        // Read in data.
        Scanner stdin = new Scanner(System.in);
        double[] radii = new double[7];
        for (int i=1; i<=6; i++)
            radii[i] = stdin.nextDouble();
        double stddev = stdin.nextDouble();
        var = stddev*stddev;

        // Add up expectation.
        double expect = 0;
        for (int i=0; i<6; i++)
            expect += (prob(radii[i], radii[i+1])*expPts[i]);
        System.out.println(expect);
    }

    // Integral of given function times area(2pir), used to evaluate probability.
    public static double f(double x) {
        return Math.exp(-x*x/(2*var));
    }

    // Probability between rings of radii r1 and r2
    public static double prob(double r1, double r2) {
        return f(r1) - f(r2);
    }
}