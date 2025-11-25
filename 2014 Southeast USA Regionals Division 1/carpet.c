#include <stdio.h>
#include <math.h>

int main() {
    double a, b, c;
    scanf("%lf %lf %lf", &a, &b, &c);

    double s = (a + b + c) / 2;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    double t = a * a + b * b + c * c;
    double carpet = (sqrt(3) / 4 * t + 3 * area) / 2;
    
    int valid_triangle = (a + b >= c && a + c >= b && b + c >= a);
    double min_side = sqrt(carpet * 4 / sqrt(3));
    int meets_condition = (min_side >= (a > b ? (a > c ? a : c) : (b > c ? b : c)));
    
    if (valid_triangle && meets_condition) {
        printf("%.3f\n", carpet);
    } else {
        printf("-1\n");
    }
    
    return 0;
}