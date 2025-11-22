#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int binomial_coefficient(int n, int k) {
    static int mem[100][100] = {{1}};
    static int max_n = 0;
    
    if (n > max_n) {
        for (int i = max_n + 1; i <= n; i++) {
            mem[i][0] = 1;
            mem[i][i] = 1;
            for (int j = 1; j < i; j++) {
                mem[i][j] = mem[i-1][j-1] + mem[i-1][j];
            }
        }
        max_n = n;
    }
    return mem[n][k];
}

double eval_at(double* a, int len, int x) {
    if (x == 0) return a[0];
    double result = 0.0;
    double power = 1.0;
    for (int i = 0; i < len; i++) {
        result += a[i] * power;
        power *= x;
    }
    return result;
}

void find_c(int n, double* a, double* c) {
    // Calculate polynomial values at points 0..n
    double points[100];
    for (int x = 0; x <= n; x++) {
        points[x] = eval_at(a, n+1, x);
    }
    
    c[0] = points[0];
    for (int i = 0; i < n; i++) {
        double sum = points[i+1] - points[i];
        for (int j = 0; j < i; j++) {
            sum -= binomial_coefficient(i, j) * c[j+1];
        }
        c[i+1] = sum;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    double a[100];
    for (int i = 0; i <= n; i++) {
        scanf("%lf", &a[i]);
    }
    
    // Reverse the array
    for (int i = 0; i <= n/2; i++) {
        double temp = a[i];
        a[i] = a[n - i];
        a[n - i] = temp;
    }
    
    double c[100];
    find_c(n, a, c);
    
    for (int i = 0; i <= n; i++) {
        printf("%.0f ", c[i]);
    }
    printf("\n");
    
    return 0;
}