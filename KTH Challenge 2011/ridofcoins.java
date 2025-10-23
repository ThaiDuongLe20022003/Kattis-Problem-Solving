import java.io.*;
import java.util.Scanner;
import java.lang.Math;

public class ridofcoins {
    public static void main(String[] args) throws IOException {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));
        int p = sc.nextInt();
        int x[] = new int[4], v[] = new int[]{1, 5, 10, 25};
        for (int i = 0; i < 4; i++)
            x[i] = sc.nextInt();

        int res = -1;
        for (int i = 0; i < 25; i++)
        {
            int use1 = Math.min(x[0], p) - i;
            if (use1 < 0) break;
            int p1 = p - use1;
            if (p1 % 5 != 0) continue;

            for (int j = 0; j < 5; j++)
            {
                int use5 = Math.min(x[1], p1 / 5) - j;
                if (use5 < 0) break;
                int p5 = p1 - use5 * 5;

                for (int k = 0; k <= 1; k++)
                {
                    if (k > x[3]) break;
                    int price = p5 - k * 25;
                    if (price < 0 || price % 10 != 0) continue;
                    int use10 = price / 10 % 5;
                    if (use10 > x[2]) continue;
                    use10 += (Math.min(x[2], price / 10) - use10) / 5 * 5;

                    int use25 = (price - 10 * use10) / 25 + k;
                    if (use25 > x[3]) continue;

                    res = Math.max(res, use1 + use5 + use10 + use25);
                }
            }
        }

        if (res == -1)
            System.out.println("Impossible");
        else
            System.out.println(res);
    }
}