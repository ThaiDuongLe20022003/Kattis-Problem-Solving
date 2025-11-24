#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Define a type for the cost. Since the C++ version uses a template <typename T>
// and the main function uses int, we'll use long long for safety in C.
typedef long long cost_t;

// Helper function for std::exchange
cost_t exchange_cost(cost_t *ptr, cost_t new_val) {
    cost_t old_val = *ptr;
    *ptr = new_val;
    return old_val;
}

int exchange_int(int *ptr, int new_val) {
    int old_val = *ptr;
    *ptr = new_val;
    return old_val;
}

// Jonker-Volgenant algorithm for minimum cost assignment
// C: cost matrix (n x m)
// n: number of rows
// m: number of columns
// Returns the minimum cost. The assignment is stored in row_match.
cost_t jonker_volgenant(cost_t **C, int n, int m, int *row_match) {
    // row_match: assignment from row to column (size n)
    // col_match: assignment from column to row (size m)
    // dist: distance/reduced cost (size m)
    // potential: column potential (size m)
    // cols: array of column indices (size m)
    // prev: predecessor array (size m)
    
    int *col_match = (int*)malloc(m * sizeof(int));
    cost_t *dist = (cost_t*)malloc(m * sizeof(cost_t));
    cost_t *potential = (cost_t*)malloc(m * sizeof(cost_t));
    int *cols = (int*)malloc(m * sizeof(int));
    int *prev = (int*)malloc(m * sizeof(int));

    for (int i = 0; i < n; i++) row_match[i] = -1;
    for (int j = 0; j < m; j++) col_match[j] = -1;
    for (int j = 0; j < m; j++) potential[j] = 0;
    for (int j = 0; j < m; j++) cols[j] = j;

    for (int i = 0; i < n; i++) {
        cost_t d = 0;
        int c1 = -1;
        int temp = 0;

        for (int c = 0; c < m; c++) {
            dist[c] = C[i][c] - potential[c];
            prev[c] = i;
        }

        int s = 0, t = 0;
        for (;;) {
            if (s == t) {
                temp = s;
                d = dist[cols[t++]];
                
                // Find minimum dist in cols[t..m-1] and move it to cols[t]
                for (int j = t; j < m; j++) {
                    c1 = cols[j];
                    if (d < dist[c1]) continue;
                    if (d > dist[c1]) {
                        d = dist[c1];
                        t = s;
                    }
                    // C++: cols[j] = exchange(cols[t++], c1);
                    int temp_c = cols[t];
                    cols[t++] = c1;
                    cols[j] = temp_c;
                }

                for (int j = s; j < t; j++) {
                    c1 = cols[j];
                    if (col_match[c1] == -1) goto done;
                }
            }

            int c2 = cols[s++];
            int r = col_match[c2];
            
            for (int j = t; j < m; j++) {
                c1 = cols[j];
                cost_t reduced_cost = C[r][c1] - C[r][c2] + potential[c2] - potential[c1] + d;
                
                if (dist[c1] > reduced_cost) {
                    dist[c1] = reduced_cost;
                    prev[c1] = r;

                    if (dist[c1] == d) {
                        if (col_match[c1] == -1) goto done;
                        // C++: cols[j] = exchange(cols[t++], c1);
                        int temp_c = cols[t];
                        cols[t++] = c1;
                        cols[j] = temp_c;
                    }
                }
            }
        }
        done:;

        for (int j = 0; j < temp; j++) potential[cols[j]] += dist[cols[j]] - d;
        
        int r = -1;
        while (r != i) {
            r = col_match[c1] = prev[c1];
            // C++: swap(c1, row_match[r]);
            int temp_c = c1;
            c1 = row_match[r];
            row_match[r] = temp_c;
        }
    }

    cost_t cost = 0;
    for (int i = 0; i < n; i++) {
        if (row_match[i] != -1) {
            cost += C[i][row_match[i]];
        }
    }
    
    free(col_match);
    free(dist);
    free(potential);
    free(cols);
    free(prev);

    return cost;
}

// Main function logic (Problem specific)
void solve() {
    int n, m;
    while (scanf("%d %d", &n, &m) == 2 && (n != 0 || m != 0)) {
        if (n == 0 && m == 0) break;
        
        int total = 0;
        int *positions = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            scanf("%d", &positions[i]);
            total += positions[i];
        }

        // cols[job] stores the column indices assigned to job
        // This is a 2D array/vector of vectors in C++
        int **cols = (int**)malloc(n * sizeof(int*));
        int *cols_size = (int*)malloc(n * sizeof(int));
        int current_col = 0;
        for (int job = 0; job < n; job++) {
            cols_size[job] = positions[job];
            cols[job] = (int*)malloc(positions[job] * sizeof(int));
            for (int k = 0; k < positions[job]; k++) {
                cols[job][k] = current_col++;
            }
        }

        // Cost matrix is (m+1) x (total+1) in C++
        // We will use m x total for the actual assignment problem
        // The C++ code uses 1-based indexing for rows and columns in the cost matrix,
        // which is a common pattern when the problem size is small and the cost matrix is padded.
        // We will stick to 0-based indexing for the Jonker-Volgenant function and adjust the input.
        
        // The problem seems to be a min-cost assignment of 'total' items to 'm' slots.
        // The C++ code uses a cost matrix of size (m+1) x (total+1).
        // Let's assume the actual dimensions are max(m, total) x max(m, total) for a square matrix,
        // or the dimensions are m x total, and the Jonker-Volgenant function handles non-square.
        // The C++ implementation handles non-square matrices (n rows, m columns).
        // Here, n_rows = m, n_cols = total.
        
        int n_rows = m;
        int n_cols = total;
        
        // The C++ code uses a cost matrix of size (m+1) x (total+1) and accesses C[i+1][j+1].
        // This suggests the actual problem size is m x total.
        cost_t **cost = (cost_t**)malloc(n_rows * sizeof(cost_t*));
        for (int i = 0; i < n_rows; i++) {
            cost[i] = (cost_t*)malloc(n_cols * sizeof(cost_t));
            for (int j = 0; j < n_cols; j++) {
                cost[i][j] = 0; // Initialize to 0
            }
        }

        for (int i = 0; i < m; i++) {
            int y, c1, c2, c3, c4;
            scanf("%d %d %d %d %d", &y, &c1, &c2, &c3, &c4);

            cost_t c = 4 * y;
            int jobs[] = {c1, c2, c3, c4};
            
            for (int k = 0; k < 4; k++) {
                int job = jobs[k];
                // The C++ code uses 1-based indexing for jobs (c1, c2, c3, c4)
                // We assume job indices are 0-based in the C++ code's context, but the problem
                // statement is not available. Given the C++ code's structure, let's assume
                // the input job indices are 0-based (0 to n-1).
                
                // The C++ code: for (int j : cols[job]) cost[i + 1][j + 1] = -c;
                // Our 0-based C code: for (int j : cols[job]) cost[i][j] = -c;
                
                if (job >= 0 && job < n) {
                    for (int l = 0; l < cols_size[job]; l++) {
                        int col_idx = cols[job][l];
                        if (i < n_rows && col_idx < n_cols) {
                            cost[i][col_idx] = -c;
                        }
                    }
                }
                c--;
            }
        }
        
        // The Jonker-Volgenant algorithm finds the minimum cost.
        // The problem seems to be a maximum cost problem, as the cost is negated.
        // The C++ code calls: -jonker_volgenant(cost).second
        
        int *row_match = (int*)malloc(n_rows * sizeof(int));
        cost_t min_cost = jonker_volgenant(cost, n_rows, n_cols, row_match);
        
        printf("%lld\n", -min_cost);

        // Cleanup
        free(row_match);
        for (int i = 0; i < n_rows; i++) free(cost[i]);
        free(cost);
        for (int i = 0; i < n; i++) free(cols[i]);
        free(cols);
        free(cols_size);
        free(positions);
    }
}

int main() {
    // Standard I/O is sufficient for C
    solve();
    return 0;
}