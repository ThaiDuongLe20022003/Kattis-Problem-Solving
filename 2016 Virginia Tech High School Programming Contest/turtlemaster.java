/** * OOP Java Project  WiSe 2023/2024

* Problem: Turtle Master

* Link: https://open.kattis.com/contests/xreb4q/problems/turtlemaster ;

* @author Nguyen Hoang Huan 

* @version 1.1, 25.10.2023

* Method : simulation, 2darrays, arraylists, enums

* Status : Accepted 

* Runtime: 0.09 */

import java.util.*;

public class turtlemaster {
    private enum Direction {
        RIGHT, DOWN, LEFT, UP
    }

    private static char[][] initializeBoard(Scanner sc) {
        char[][] board = new char[8][8];
        for (int r = 0; r < 8; r++) {
            board[r] = sc.nextLine().toCharArray();
        }
        return board;
    }

    private static boolean move(Direction direction, char[][] board, int[] position) {
        int r = position[0] + directionMove(direction)[0];
        int c = position[1] + directionMove(direction)[1];

        if (isOutOfBounds(r, c) || board[r][c] == 'I' || board[r][c] == 'C') {
            return false;
        }

        board[position[0]][position[1]] = '.';
        board[r][c] = 'T';

        position[0] = r;
        position[1] = c;
        return true;
    }

    private static boolean shoot(Direction direction, char[][] board, int[] position) {
        int r = position[0] + directionMove(direction)[0];
        int c = position[1] + directionMove(direction)[1];

        if (isOutOfBounds(r, c) || board[r][c] != 'I') {
            return false;
        }

        board[r][c] = '.';
        return true;
    }

    private static int[] directionMove(Direction direction) {
        switch (direction) {
            case RIGHT:
                return new int[]{0, 1};
            case DOWN:
                return new int[]{1, 0};
            case LEFT:
                return new int[]{0, -1};
            case UP:
                return new int[]{-1, 0};
            default:
                return new int[]{0, 0};
        }
    }

    private static boolean isOutOfBounds(int r, int c) {
        return r < 0 || r >= 8 || c < 0 || c >= 8;
    }

    public static void main(String[] args) {
        try (Scanner sc = new Scanner(System.in)) {
            char[][] board = initializeBoard(sc);
            ArrayList<int[]> diamondPositions = new ArrayList<>();
            int[] position = {7, 0};
            Direction direction = Direction.RIGHT;

            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    if (board[r][c] == 'D') {
                        diamondPositions.add(new int[]{r, c});
                    }
                }
            }

            boolean diamond = true;
            for (char command : sc.nextLine().toCharArray()) {
                switch (command) {
                    case 'F':
                        if (!move(direction, board, position)) {
                            diamond = false;
                        }
                        break;
                    case 'L':
                        direction = Direction.values()[(direction.ordinal() + 3) % 4];
                        break;
                    case 'R':
                        direction = Direction.values()[(direction.ordinal() + 1) % 4];
                        break;
                    case 'X':
                        if (!shoot(direction, board, position)) {
                            diamond = false;
                        }
                        break;
                }
            }

            if (diamond) {
                diamond = false;
                for (int[] diamondPos : diamondPositions) {
                    if (diamondPos[0] == position[0] && diamondPos[1] == position[1]) {
                        diamond = true;
                        break;
                    }
                }
            }

            System.out.println(diamond ? "Diamond!" : "Bug!");
        }
    }
}