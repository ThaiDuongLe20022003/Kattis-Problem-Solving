import java.io.*;
import java.util.*;

public class theimp
{
    BufferedReader br;
    PrintWriter out;
    StringTokenizer st;
    boolean eof;
    public static final int INF=(1<<29);


    void solve() throws IOException 
    {
        int test=nextInt();
        while(test-->0)
        {
            int n=nextInt();
            int k=nextInt();
            ArrayList<Pair> trs = new ArrayList<Pair>();
            for(int i=0;i<n;i++)
            {
                int val=nextInt();
                int cost=nextInt();
                trs.add(new Pair(val,cost));
            }
            Collections.sort(trs);
            int[][] dp=new int[k+1][n+1];
            for(int j=0;j<=k;j++) dp[j][n]=-INF;
            for(int i=n-1;i>=0;i--) dp[k][i]=Math.max(dp[k][i+1],trs.get(i).v-trs.get(i).c);
            for(int j=k-1;j>=0;j--) for(int i=n-1;i>=0;i--) dp[j][i]=Math.max(dp[j][i+1],Math.min(dp[j+1][i+1], trs.get(i).v)-trs.get(i).c);
            out.println(Math.max(0,dp[0][0]));
        }
        
    }

    theimp() throws IOException 
    {
        br=new BufferedReader(new InputStreamReader(System.in));
        out=new PrintWriter(System.out);
        solve();
        out.close();
    }

    public static void main(String[] args) throws IOException 
    {
        new theimp();
    }

    String nextToken() 
    {
        while (st==null || !st.hasMoreTokens()) 
        {
            try 
            {
                st=new StringTokenizer(br.readLine());
            } 
            catch (Exception e) 
            {
                eof=true;
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
            eof=true;
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
    
    class Pair implements Comparable<Pair>
    {
        Integer v, c;
        @Override
        public int compareTo(Pair o) 
        {
            int rComp=v.compareTo(o.v);
            if (rComp!=0) return rComp;
            return c.compareTo(o.c);
        }
        public Pair(Integer v, Integer c) 
        {
            super();
            this.v=v;
            this.c=c;
        }
        @Override
        public String toString() 
        {
            return "Pair [v=" + v + ", c=" + c + "]";
        }
    }
}