using System;

public class Program
{
    static double GetDist(double bigX, double bigY, int x, int y, int s, int r)
    {
        double smallX = (s / 100.0) * bigX;
        double smallY = (s / 100.0) * bigY;

        double tempR = Math.Sqrt(smallX * smallX + smallY * smallY);
        double theta = Math.Atan2(bigY, bigX);

        theta += r * 2 * Math.PI / 360.0;

        smallX = Math.Cos(theta) * tempR + x;
        smallY = Math.Sin(theta) * tempR + y;

        double dist = Math.Sqrt(Math.Pow(bigX - smallX, 2) + Math.Pow(bigY - smallY, 2));
        return dist;
    }

    public static void Main()
    {
        string line;
        while ((line = Console.ReadLine()) != null)
        {
            string[] tokens = line.Split();
            int w = int.Parse(tokens[0]);
            int h = int.Parse(tokens[1]);
            int x = int.Parse(tokens[2]);
            int y = int.Parse(tokens[3]);
            int s = int.Parse(tokens[4]);
            int r = int.Parse(tokens[5]);
            
            if (w == 0 && h == 0 && x == 0 && y == 0 && s == 0 && r == 0)
                break;

            double minx = 0, maxx = w;
            double miny = 0, maxy = h;

            while (maxx - minx > 0.0000001)
            {
                double scalex = maxx - minx;
                double scaley = maxy - miny;

                double lx = scalex * 0.25 + minx;
                double hx = scalex * 0.75 + minx;
                double ly = scaley * 0.25 + miny;
                double hy = scaley * 0.75 + miny;

                double d1 = GetDist(lx, ly, x, y, s, r);
                double d2 = GetDist(hx, ly, x, y, s, r);
                double d3 = GetDist(lx, hy, x, y, s, r);
                double d4 = GetDist(hx, hy, x, y, s, r);

                double avgx = (minx + maxx) / 2;
                double avgy = (miny + maxy) / 2;

                if (d1 < d2 && d1 < d3 && d1 < d4)
                {
                    maxx = avgx;
                    maxy = avgy;
                }
                else if (d2 < d1 && d2 < d3 && d2 < d4)
                {
                    minx = avgx;
                    maxy = avgy;
                }
                else if (d3 < d2 && d3 < d1 && d3 < d4)
                {
                    maxx = avgx;
                    miny = avgy;
                }
                else if (d4 < d2 && d4 < d3 && d4 < d1)
                {
                    minx = avgx;
                    miny = avgy;
                }
            }

            Console.WriteLine($"{minx:F2} {miny:F2}");
        }
    }
}