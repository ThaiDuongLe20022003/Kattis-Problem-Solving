import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class goodmorning {
    static Map<String, Position> d = new HashMap<>();

    static {
        d.put("1", new Position(0, 0));
        d.put("2", new Position(1, 0));
        d.put("3", new Position(2, 0));
        d.put("4", new Position(0, 1));
        d.put("5", new Position(1, 1));
        d.put("6", new Position(2, 1));
        d.put("7", new Position(0, 2));
        d.put("8", new Position(1, 2));
        d.put("9", new Position(2, 2));
        d.put("0", new Position(1, 3));
    }

    public static class Position {
        public int x, y;

        public Position(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static boolean checkAlign(Position left, Position right) {
        return (right.x >= left.x && right.y >= left.y);
    }

    static boolean checkAllAlign(int n) {
        String a, b, c, temp;
        if (n < 10) {
            return true;
        } else if (n >= 10 && n <= 99) {
            temp = Integer.toString(n);
            a = temp.substring(0, 1);
            b = temp.substring(1, 2);
            return checkAlign(d.get(a), d.get(b));
        } else {
            temp = Integer.toString(n);
            a = temp.substring(0, 1);
            b = temp.substring(1, 2);
            c = temp.substring(2, 3);
            return checkAlign(d.get(a), d.get(b)) && checkAlign(d.get(b), d.get(c));
        }
    }

    static int findClosest(int n) {
        if (n < 10) {
            return n;
        } else {
            if (checkAllAlign(n)) {
                return n;
            } else {
                int up = n + 1, down = n - 1;
                while (true) {
                    if (checkAllAlign(up)) {
                        return up;
                    } else if (checkAllAlign(down)) {
                        return down;
                    }
                    up++;
                    down--;
                }
            }
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        int tc = scanner.nextInt();
        for (int i = 0; i < tc; i++) {
            int n = scanner.nextInt();
            System.out.println(findClosest(n));
        }
    }
}