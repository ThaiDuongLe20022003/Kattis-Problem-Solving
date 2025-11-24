import java.util.Scanner;

public class overlappingmaps {
    static double getDist(double bigX, double bigY, int x, int y, int s, int r) {
        double smallX = (s / 100.0) * bigX;
        double smallY = (s / 100.0) * bigY;

        double tempR = Math.sqrt(smallX * smallX + smallY * smallY);
        double theta = Math.atan2(bigY, bigX);

        theta += r * 2 * Math.PI / 360.0;

        smallX = Math.cos(theta) * tempR + x;
        smallY = Math.sin(theta) * tempR + y;

        double dist = Math.sqrt(Math.pow(bigX - smallX, 2) + Math.pow(bigY - smallY, 2));
        return dist;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        while (scanner.hasNext()) {
            int w = scanner.nextInt();
            int h = scanner.nextInt();
            int x = scanner.nextInt();
            int y = scanner.nextInt();
            int s = scanner.nextInt();
            int r = scanner.nextInt();
            
            if (w == 0 && h == 0 && x == 0 && y == 0 && s == 0 && r == 0)
                break;

            double minx = 0, maxx = w;
            double miny = 0, maxy = h;

            while (maxx - minx > 0.0000001) {
                double scalex = maxx - minx;
                double scaley = maxy - miny;

                double lx = scalex * 0.25 + minx;
                double hx = scalex * 0.75 + minx;
                double ly = scaley * 0.25 + miny;
                double hy = scaley * 0.75 + miny;

                double d1 = getDist(lx, ly, x, y, s, r);
                double d2 = getDist(hx, ly, x, y, s, r);
                double d3 = getDist(lx, hy, x, y, s, r);
                double d4 = getDist(hx, hy, x, y, s, r);

                double avgx = (minx + maxx) / 2;
                double avgy = (miny + maxy) / 2;

                if (d1 < d2 && d1 < d3 && d1 < d4) {
                    maxx = avgx;
                    maxy = avgy;
                } else if (d2 < d1 && d2 < d3 && d2 < d4) {
                    minx = avgx;
                    maxy = avgy;
                } else if (d3 < d2 && d3 < d1 && d3 < d4) {
                    maxx = avgx;
                    miny = avgy;
                } else if (d4 < d2 && d4 < d3 && d4 < d1) {
                    minx = avgx;
                    miny = avgy;
                }
            }

            System.out.printf("%.2f %.2f\n", minx, miny);
        }
        
        scanner.close();
    }
}