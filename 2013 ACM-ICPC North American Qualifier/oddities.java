import java.util.Scanner;

public class oddities {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        
        for (int i = 0; i < n; i++) {
            int next = scanner.nextInt();
            
            if ((next & 1) == 1) {
                System.out.println(next + " is odd");
            } else {
                System.out.println(next + " is even");
            }
        }
        
        scanner.close();
    }
}