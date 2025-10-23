import java.util.Scanner;

public class soylent {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        StringBuilder sb = new StringBuilder();
        int t = sc.nextInt();
        for(int i = 0; i < t; i++) {
            int cals = sc.nextInt();
            double num = (cals * 1.0) / 400;
            int out = (int) num;
            if (num > out) {
                out++;
            }
            sb.append(out);
            sb.append("\n");
        }
        System.out.print(sb);
    }
}