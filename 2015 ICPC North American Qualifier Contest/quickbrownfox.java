import java.util.Scanner;

public class quickbrownfox {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = Integer.parseInt(scanner.nextLine());
        
        for(int i = 0; i < n; i++) {
            boolean[] letters = new boolean[26];
            String s = scanner.nextLine();
            int used = 0;
            
            for(char c : s.toCharArray()) {
                int temp = Character.toLowerCase(c) - 'a';
                if(temp < 26 && temp >= 0 && !letters[temp]) {
                    letters[temp] = true;
                    used++;
                }
            }
            
            if(used == 26) {
                System.out.print("pangram");
            } else {
                System.out.print("missing ");
                for(int j = 0; j < 26; j++) {
                    if(!letters[j]) {
                        System.out.print((char)(j + 'a'));
                    }
                }
            }
            
            System.out.println();
        }
        
        scanner.close();
    }
}