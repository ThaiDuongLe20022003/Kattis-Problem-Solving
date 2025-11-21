import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int ntests = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        String fi = "Chikapu";
        String se = "Bash";
        
        for (int i = 0; i < ntests; i++) {
            String s = scanner.nextLine();
            int n = s.length();
            
            if (s.charAt(0) != s.charAt(n - 1)) {
                System.out.println((n % 2 == 0) ? se : fi);
            } else {
                System.out.println((n % 2 == 1) ? se : fi);
            }
        }
    }
}