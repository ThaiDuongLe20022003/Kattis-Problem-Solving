import java.io.*;
import java.util.*;

public class cantstopplaying
{
    BufferedReader br;
    PrintWriter out;
    StringTokenizer st;
    boolean eof;
    public static final int INF=(1<<29);
    int[] ispower;
    int[] possible;
    
    int get_next_left(int old,int x,int oldsum)
    {
        int a=old,b=oldsum-a;
        if (a%x==0) a+=x;
        else return -1;
        if (ispower[a]!=-1)
        {
            if (2*a>b) 
            {
                b+=a;
                a=0;
            }
        }
        return a;
    }

    int get_next_right(int old,int x,int oldsum)
    {
        int a=old,b=oldsum-a;
        if (b%x==0) b+=x;
        else return -1;
        if (ispower[b]!=-1)
        {
            if (2*b>a) 
            {
                a+=b;
                b=0;
            }
        }
        return a;
    }


    void solve() throws IOException 
    {
        ispower=new int[1<<18];
        possible=new int[1<<18];
        for(int i=0;i<(1<<18);i++) ispower[i]=-1;
        for(int i=0;i<18;i++) ispower[1<<i]=i;
        int test=nextInt();
        while(test-->0)
        {
            int n=nextInt();
            int sum=0;
            int[] num=new int[n];
            for(int i=0;i<n;i++) 
            {
                num[i]=nextInt();
                sum+=num[i];
            }
            if (ispower[sum]==-1) {out.println("no");continue;}
            int[][] v = new int[n+1][];
            int[] len = new int[n+1];
            v[0]=new int[1];
            v[0][0]=0;
            len[0]=1;
            sum=0;
            for(int i=1;i<=n;i++)
            {
                int x=num[i-1];
                ArrayList<Integer> pos=new ArrayList<Integer>();
                for(int j=0;j<len[i-1];j++)
                {
                    int y=v[i-1][j];
                    int yn[]={get_next_right(y,x,sum),get_next_left(y,x,sum)};
                    for(int k=0;k<2;k++)
                    {
                        if (yn[k]>=0 && possible[yn[k]]==0)
                        {
                            possible[yn[k]]=1;
                            pos.add(yn[k]);
                        }
                    }
                }
                len[i]=pos.size();
                v[i]=new int[len[i]];
                for(int j=0;j<len[i];j++) v[i][j]=pos.get(j);
                for(int j=0;j<pos.size();j++) possible[pos.get(j)]=0;
                sum+=x;
            }
            
            
            int b=-1;
            for(int i=0;i<len[n];i++) if (v[n][i]==0 || v[n][i]==sum) b=i;
            if (b<0) {out.println("no");continue;}
            String s = new String();
            for(int i=n-1;i>=0;i--)
            {
                int akt=v[i+1][b];
                sum-=num[i];
                for(int j=0;j<len[i];j++)
                {
                    if (get_next_left(v[i][j],num[i],sum)==akt) {b=j;s+="l";break;}
                    if (get_next_right(v[i][j],num[i],sum)==akt) {b=j;s+="r";break;}
                }
            }
            for(int i=n-1;i>=0;i--) out.print(s.charAt(i));
            out.println("");
        }
        
    }

    cantstopplaying() throws IOException 
    {
        br=new BufferedReader(new InputStreamReader(System.in));
        out=new PrintWriter(System.out);
        solve();
        out.close();
    }

    public static void main(String[] args) throws IOException 
    {
        new cantstopplaying();
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