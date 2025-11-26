import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int times = scanner.nextInt();
        scanner.nextLine(); // consume newline
        
        for(int i = 0; i < times; i++) {
            String s = scanner.nextLine();
            
            if(s.startsWith("Simon says")) {
                String result = s.substring(11);
                System.out.println(result);
            }
        }
        
        scanner.close();
    }
}