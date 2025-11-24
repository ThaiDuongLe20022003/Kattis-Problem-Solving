#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

typedef struct {
    double x, y;
} Point;

double euclidean_dist(const Point *a, const Point *b) {
    return sqrt((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

typedef struct {
    double value;
    double *solution;
    int solution_size;
} LPResult;

// Pivot helper: performs pivot on tableau at (row,col) and updates basis
static void pivot_func(double **tableau, int m, int n, int *basic, int *non_basic, int row, int col) {
    double inv = 1.0 / tableau[row][col];

    for (int i = 0; i < m + 2; i++) {
        if (i != row && fabs(tableau[i][col]) > 1e-8) {
            double temp = tableau[i][col] * inv;
            for (int j = 0; j < n + 2; j++) {
                tableau[i][j] -= tableau[row][j] * temp;
            }
            tableau[i][col] = tableau[row][col] * temp;
        }
    }

    for (int i = 0; i < m + 2; i++) {
        if (i != row) {
            tableau[i][col] *= -inv;
        }
    }

    for (int j = 0; j < n + 2; j++) {
        if (j != col) {
            tableau[row][j] *= inv;
        }
    }
    tableau[row][col] = inv;

    int temp = basic[row];
    basic[row] = non_basic[col];
    non_basic[col] = temp;
}

// Simplex helper: runs simplex phase (1 or 2) on the given tableau
static int simplex_func(int phase, double **tableau, int m, int n, int *basic, int *non_basic) {
    while (1) {
        int r = m + (phase == 1 ? 1 : 0);
        int col = -1;

        for (int j = 0; j <= n; j++) {
            if (phase == 2 && non_basic[j] == -1) continue;
            if (col == -1 || tableau[r][j] < tableau[r][col] - 1e-8 ||
                (fabs(tableau[r][j] - tableau[r][col]) < 1e-8 && non_basic[j] < non_basic[col])) {
                col = j;
            }
        }

        if (tableau[r][col] >= -1e-8) return 1;

        int row = -1;
        for (int i = 0; i < m; i++) {
            if (tableau[i][col] <= 1e-8) continue;
            double lhs = tableau[i][n + 1] / tableau[i][col];
            double rhs = row == -1 ? 0 : tableau[row][n + 1] / tableau[row][col];
            if (row == -1 || lhs < rhs - 1e-8 ||
                (fabs(lhs - rhs) < 1e-8 && basic[i] < basic[row])) {
                row = i;
            }
        }

        if (row == -1) return 0;
        pivot_func(tableau, m, n, basic, non_basic, row, col);
    }
}

LPResult linear_program_solution(double **A, double *b, double *c, int m, int n) {
    LPResult result = {0};
    result.solution = NULL;
    result.solution_size = n;
    
    // Allocate tableau
    double **tableau = (double **)malloc((m + 2) * sizeof(double *));
    for (int i = 0; i < m + 2; i++) {
        tableau[i] = (double *)malloc((n + 2) * sizeof(double));
        memset(tableau[i], 0, (n + 2) * sizeof(double));
    }
    
    int *basic = (int *)malloc(m * sizeof(int));
    int *non_basic = (int *)malloc((n + 1) * sizeof(int));
    
    // Initialize tableau
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            tableau[i][j] = A[i][j];
        }
        basic[i] = n + i;
        tableau[i][n] = -1;
        tableau[i][n + 1] = b[i];
    }
    
    for (int j = 0; j <= n; j++) {
        non_basic[j] = j;
    }
    non_basic[n] = -1;
    
    for (int j = 0; j < n; j++) {
        tableau[m][j] = -c[j];
    }
    tableau[m + 1][n] = 1;
    
    // Note: pivot and simplex are implemented as top-level static helpers (see below).
    
    int row = 0;
    for (int i = 1; i < m; i++) {
        if (tableau[i][n + 1] < tableau[row][n + 1]) {
            row = i;
        }
    }
    
    if (tableau[row][n + 1] <= -1e-8) {
        pivot_func(tableau, m, n, basic, non_basic, row, n);
        if (!simplex_func(1, tableau, m, n, basic, non_basic) || tableau[m + 1][n + 1] < -1e-8) {
            result.value = -INFINITY;
            goto cleanup;
        }
        
        for (int i = 0; i < m; i++) {
            if (basic[i] == -1) {
                int col = -1;
                for (int j = 0; j <= n; j++) {
                    if (col == -1 || tableau[i][j] < tableau[i][col] - 1e-8 ||
                        (fabs(tableau[i][j] - tableau[i][col]) < 1e-8 && non_basic[j] < non_basic[col])) {
                        col = j;
                    }
                }
                pivot_func(tableau, m, n, basic, non_basic, i, col);
            }
        }
    }
    
    if (!simplex_func(2, tableau, m, n, basic, non_basic)) {
        result.value = INFINITY;
        goto cleanup;
    }
    
    result.solution = (double *)malloc(n * sizeof(double));
    memset(result.solution, 0, n * sizeof(double));
    for (int i = 0; i < m; i++) {
        if (basic[i] < n) {
            result.solution[basic[i]] = tableau[i][n + 1];
        }
    }
    result.value = tableau[m][n + 1];
    
cleanup:
    for (int i = 0; i < m + 2; i++) {
        free(tableau[i]);
    }
    free(tableau);
    free(basic);
    free(non_basic);
    
    return result;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Point *coords = (Point *)malloc(n * sizeof(Point));
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &coords[i].x, &coords[i].y);
    }
    
    int m = n * (n - 1) / 2;
    
    double **A = (double **)malloc(m * sizeof(double *));
    for (int i = 0; i < m; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        memset(A[i], 0, n * sizeof(double));
    }
    
    double *b = (double *)malloc(m * sizeof(double));
    double *c = (double *)malloc(n * sizeof(double));
    
    for (int i = 0; i < n; i++) {
        c[i] = 1.0;
    }
    
    int k = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            A[k][i] = 1.0;
            A[k][j] = 1.0;
            b[k] = euclidean_dist(&coords[i], &coords[j]);
            k++;
        }
    }
    
    LPResult result = linear_program_solution(A, b, c, m, n);
    printf("%.2f\n", result.value);
    
    // Cleanup
    free(coords);
    for (int i = 0; i < m; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(c);
    if (result.solution) free(result.solution);
    
    return 0;
}