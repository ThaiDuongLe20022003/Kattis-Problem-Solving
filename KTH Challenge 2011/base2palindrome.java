import java.io.*;

public class base2palindrome {
    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        long n = Long.parseLong(in.readLine()) - 1;
        for (int l = 1; l <= 31; l++)
        {
            int len = (l + 1) / 2 - 1;
            long cnt = 1 << len;
            if (n < cnt)
            {
                char b[] = Long.toBinaryString((n + cnt) << (l - 1 - len)).toCharArray();
                for (int i = 0; i <= len; i++)
                    b[l - 1 - i] = b[i];
                long res = 0;
                for (int i = 0; i < l; i++)
                    res += (long)Character.getNumericValue(b[i]) << i;
                System.out.println(res);
                break;
            }
            else n -= cnt;
        }
    }
}