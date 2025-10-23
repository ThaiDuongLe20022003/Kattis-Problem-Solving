import java.io.*;
import java.util.Scanner;
import java.lang.Math;

public class excursion {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String s = in.readLine();

        int cnt[] = new int[3];
        long res = 0;
        for (int i = 0; i < s.length(); i++)
        {
            for (int j = Character.digit(s.charAt(i), 10) + 1; j <= 2; j++)
                res += cnt[j];
            cnt[Character.digit(s.charAt(i), 10)]++;
        }
        System.out.println(res);
    }
}