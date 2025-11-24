#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double getdist(double bigX, double bigY, int x, int y, int s, int r) {
    double smallX = (s / 100.0) * bigX;
    double smallY = (s / 100.0) * bigY;

    double tempR = sqrt(smallX * smallX + smallY * smallY);
    double theta = atan2(bigY, bigX);

    theta += r * 2 * M_PI / 360.0;

    smallX = cos(theta) * tempR + x;
    smallY = sin(theta) * tempR + y;

    double dist = sqrt(pow(bigX - smallX, 2) + pow(bigY - smallY, 2));
    return dist;
}

int main() {
    int w, h, x, y, s, r;
    
    while (scanf("%d %d %d %d %d %d", &w, &h, &x, &y, &s, &r) == 6) {
        if (!(w || h || x || y || s || r)) break;

        double minx = 0, maxx = w;
        double miny = 0, maxy = h;

        while (maxx - minx > 0.0000001) {
            double scalex = maxx - minx;
            double scaley = maxy - miny;

            double lx = scalex * 0.25 + minx;
            double hx = scalex * 0.75 + minx;
            double ly = scaley * 0.25 + miny;
            double hy = scaley * 0.75 + miny;

            double d1 = getdist(lx, ly, x, y, s, r);
            double d2 = getdist(hx, ly, x, y, s, r);
            double d3 = getdist(lx, hy, x, y, s, r);
            double d4 = getdist(hx, hy, x, y, s, r);

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

        printf("%.2f %.2f\n", minx, miny);
    }
    
    return 0;
}