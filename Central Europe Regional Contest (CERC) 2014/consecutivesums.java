import java.io.*;
import java.util.*;

public class consecutivesums 
{
    BufferedReader br;
    PrintWriter out;
    StringTokenizer st;
    boolean eof;



    void solve() throws IOException 
    {
        Locale.setDefault(Locale.US);
        int test = nextInt();
        while(test-->0)
        {
            int n = nextInt();
            int L = n+1;
            int limit=Math.min((int)(2*Math.sqrt(n)),n);
            for(int l=2;l<=limit;l++)
            {
                long k=((2*n)/l-l+1)/2;
                if (k>0 && l*(2*k+l-1)==2*n)
                {
                    L=l;
                    break;
                }
            }
            if (L<=n)
            {
                int K=(2*n/L-L+1)/2;
                out.print(String.format("%d = ",n));
                for(int i=0;i<L-1;i++) out.print(String.format("%d + ",K+i));
                out.println(K+L-1);
            }
            else out.println("IMPOSSIBLE");
        }
        
    }

    consecutivesums() throws IOException 
    {
        br = new BufferedReader(new InputStreamReader(System.in));
        out = new PrintWriter(System.out);
        solve();
        out.close();
    }

    public static void main(String[] args) throws IOException 
    {
        new consecutivesums();
    }

    String nextToken() 
    {
        while (st == null || !st.hasMoreTokens()) 
        {
            try 
            {
                st = new StringTokenizer(br.readLine());
            } 
            catch (Exception e) 
            {
                eof = true;
                return null;
            }
        }
        return st.nextToken();
    }

    String nextString() 
    {
        try 
        {
            return br.readLine();
        } 
        catch (IOException e) 
        {
            eof = true;
            return null;
        }
    }

    int nextInt() throws IOException 
    {
        return Integer.parseInt(nextToken());
    }

    long nextLong() throws IOException 
    {
        return Long.parseLong(nextToken());
    }

    double nextDouble() throws IOException 
    {
        return Double.parseDouble(nextToken());
    }
}