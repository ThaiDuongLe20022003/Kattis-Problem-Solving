import java.io.*;
import java.util.*;

public class wheels
{
    BufferedReader br;
    PrintWriter out;
    StringTokenizer st;
    boolean eof;
    
    long gcd(long a,long b)
    {
        if (a==0) return b;
        return gcd(b%a,a);
    }
    

    void solve() throws IOException 
    {
        int test=nextInt();
        while(test-->0)
        {
            int n=nextInt();
            long[] x=new long[n];
            long[] y=new long[n];
            long[] r=new long[n];
            int[] move=new int[n];
            for(int i=0;i<n;i++)
            {
                x[i]=nextInt();
                y[i]=nextInt();
                r[i]=nextInt();
            }
            Stack<Integer> st=new Stack<Integer>();
            st.push(0);
            move[0]=1;
            while(!st.empty())
            {
                Integer u=(Integer)st.pop();
                for(int i=0;i<n;i++)
                {
                    if (move[i]!=0) continue;
                    if ((x[u]-x[i])*(x[u]-x[i])+(y[u]-y[i])*(y[u]-y[i])!=(r[u]+r[i])*(r[u]+r[i])) continue;
                    move[i]=-move[u];
                    st.push(new Integer(i));
                }
            }
            for(int i=0;i<n;i++)
            {
                if (move[i]==0) out.println("not moving");
                else
                {
                    long d=gcd(r[0],r[i]);
                    if (r[i]==d) out.print(r[0]/d);
                    else
                    {
                        out.print(r[0]/d);
                        out.print("/");
                        out.print(r[i]/d);
                    }
                    if (move[i]==1) out.println(" clockwise");
                    else out.println(" counterclockwise");
                }
            }
        }
        
    }

    wheels() throws IOException 
    {
        br=new BufferedReader(new InputStreamReader(System.in));
        out=new PrintWriter(System.out);
        solve();
        out.close();
    }

    public static void main(String[] args) throws IOException 
    {
        new wheels();
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
    
}