import java.util.Scanner;

public class vemvinner {
    public static void main(String[] args) {
        String[] players = {"Johan", "Abdullah"};
        Scanner scanner = new Scanner(System.in);
        
        String[][] grid = new String[3][3];
        for (int i = 0; i < 3; i++) {
            grid[i] = scanner.nextLine().split(" ");
        }

        for (int i = 0; i < 3; i++) {
            String player = grid[1][i];
            if (player.equals("_")) {
                continue;
            }

            if (player.equals(grid[0][i]) && player.equals(grid[2][i])) {
                System.out.println(players[player.equals("X") ? 0 : 1] + " har vunnit");
                System.exit(0);
            }
        }

        for (int i = 0; i < 3; i++) {
            String player = grid[i][1];
            if (player.equals("_")) {
                continue;
            }

            if (player.equals(grid[i][0]) && player.equals(grid[i][2])) {
                System.out.println(players[player.equals("X") ? 0 : 1] + " har vunnit");
                System.exit(0);
            }
        }

        String centerPlayer = grid[1][1];
        if (centerPlayer.equals("_")) {
            System.out.println("ingen har vunnit");
            System.exit(0);
        }

        if (centerPlayer.equals(grid[0][0]) && centerPlayer.equals(grid[2][2])) {
            System.out.println(players[centerPlayer.equals("X") ? 0 : 1] + " har vunnit");
            System.exit(0);
        }

        if (centerPlayer.equals(grid[2][0]) && centerPlayer.equals(grid[0][2])) {
            System.out.println(players[centerPlayer.equals("X") ? 0 : 1] + " har vunnit");
            System.exit(0);
        }

        System.out.println("ingen har vunnit");
    }
}