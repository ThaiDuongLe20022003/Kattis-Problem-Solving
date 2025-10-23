import java.util.*;

public class mravi {
    public static void main(String[] args) {
        Scanner sin = new Scanner(System.in);
        int n = sin.nextInt();
        int [] parent = new int[n+1];
        int [] perc = new int [n+1];
        int [] issuper = new int [n+1];

        for (int i=1;i<n;i++) {
            int a = sin.nextInt();
            int b = sin.nextInt();
            parent[b] = a;
            perc[b] = sin.nextInt();
            issuper[b] = sin.nextInt();
        }

        // int[] needs = new int[n+1];

        double best = 0;

        for (int i =1;i<n+1;i++) {
            double ans = sin.nextDouble();
            if (ans>=0) {
                int j =i;
                while (j>1){
                    if (issuper[j]==1) {
                        ans = Math.sqrt(ans);
                    }
                    ans *= (100.0/perc[j]);
                    j= parent[j];
                }
                if (ans>best) {
                    best=ans;
                }
            }
        }

        System.out.println(best);

    }
}