import java.io.*;
import java.util.*;

public class vocabulary
{
    static final int  A = 26;
    static final int  A2 = A + 2;
    static final char B = 'a' - 1;
    static final long M = 1000000009;

    public static void main(String[] args) throws IOException 
    {
        int[][] options = new int[A+2][];
        options[A+1] = new int[A];
        for (int i=0; i<=A; i++)
            options[i] = new int[] { i };
        for (int i=1; i<=A; i++)
            options[A+1][i-1] = i;
        int[][][] transitions = new int[A2*A2*A2][27][];
        int[] ts = new int[27];
        for (int s=0; s<27; s++)
        {
            int s0 = s / 9, s1 = (s / 3) % 3, s2 = s % 3;
            for (int m=0; m<A2*A2*A2; m++) {
                int m0 = m / (A2 * A2);
                int m1 = (m / A2) % A2;
                int m2 = m % A2;
                int[] factors = new int[27];
                for (int c0 : options[m0])
                    for (int c1 : options[m1])
                        for (int c2 : options[m2])
                        {
                            int r0 = (3*c0+s0 > 3*c1+s1 ? 1 : 0) + (3*c0+s0 > 3*c2+s2 ? 1 : 0);
                            int r1 = (3*c1+s1 > 3*c0+s0 ? 1 : 0) + (3*c1+s1 > 3*c2+s2 ? 1 : 0);
                            int r2 = (3*c2+s2 > 3*c0+s0 ? 1 : 0) + (3*c2+s2 > 3*c1+s1 ? 1 : 0);
                            factors[r0 * 9 + r1 * 3 + r2]++;
                        }
                int ts_size = 0;
                for (int t=0; t<27; t++)
                    if (factors[t] > 0)
                        ts[ts_size++] = factors[t] * 32 + t;
                transitions[m][s] = new int[ts_size];
                for (int i=0; i<ts_size; ++i)
                    transitions[m][s][i] = ts[i];
            }
        }
        BufferedReader rd = new BufferedReader(new InputStreamReader(System.in));
        PrintWriter wr = new PrintWriter(System.out);
        int T = Integer.parseInt(rd.readLine());
        for (int tt=0; tt<T; tt++)
        {
            String[] words = new String[3];
            for (int i=0; i<3; i++)
                words[i] = rd.readLine().replace('?', (char)('z'+1));
            int maxlen = 0;
            for (int i=0; i<3; i++)
                maxlen = Math.max(maxlen, words[i].length());
            for (int i=0; i<3; i++)
                words[i] = words[i] + new String(new char[maxlen-words[i].length()]).replace('\0', B);
            long[] counts = new long[27];
            counts[0] = 1;
            long[] newcounts = new long[27];
            for (int j=maxlen-1; j>=0; j--)
            {
                int c0 = words[0].charAt(j) - B;
                int c1 = words[1].charAt(j) - B;
                int c2 = words[2].charAt(j) - B;
                int c = c0*A2*A2+c1*A2+c2;
                for (int s=0; s<27; s++)
                    for (int t : transitions[c][s])
                        newcounts[t % 32] += (counts[s] * (t / 32));
                for (int s=0; s<27; s++) {
                    counts[s] = newcounts[s] % M;
                    newcounts[s] = 0;
                }
            }
            wr.println(counts[0 * 9 + 1 * 3 + 2] % M);
        }
        wr.close();
    }
}