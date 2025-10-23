import java.util.Scanner;

public class cyaniderivers {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        int longestZeros = 0;

        int dist = 0;
        for (int i = 0; i < line.length(); i++) {
            if(line.charAt(i) == '1') {
                longestZeros = Math.max(longestZeros, dist);
                dist = 0;
            } else if(line.charAt(i) == '0'){
                dist++;
            }
        }

        System.out.println((int)Math.ceil(longestZeros / 2f));
    }

}