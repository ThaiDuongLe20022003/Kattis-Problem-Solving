import java.util.Scanner;
import java.util.ArrayList;
public class numberfun {
   public static boolean cal(double a, double b, double c) {
      return a+b==c || a-b==c || b-a==c || a*b==c || a/b==c || b/a == c;
   }
   
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      ArrayList<String> r = new ArrayList<String>();
      int n = in.nextInt();
      for (int i=0;i<n;i++) {
         int a,b,c;
         a = in.nextInt();
         b = in.nextInt();
         c = in.nextInt();
         r.add(cal(a,b,c)?"Possible":"Impossible");
      }
      for (int i=0;i<r.size();i++) {
         System.out.println(r.get(i));
      }
   }
}