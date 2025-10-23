#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <string>
#include <numeric>   // For std::iota
#include <algorithm> // For std::reverse, std::swap
#include <ctime>     // For clock()
#include <cstdlib>   // For rand()

// Store x, y coordinates
struct Point {
    double x, y;
};

// Calculate Euclidean distance and round to nearest integer
long long calc_dist(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return (long long)round(sqrt(dx * dx + dy * dy));
}

// Calculate the total length of a tour (a cycle)
long long calc_tour_length(const std::vector<int>& tour, int n, 
                           const std::vector<std::vector<long long>>& dist_matrix) {
    long long length = 0;
    for (int i = 0; i < n; ++i) {
        length += dist_matrix[tour[i]][tour[(i + 1) % n]];
    }
    return length;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Seed the random number generator
    srand(time(0));

    int n;
    std::cin >> n;

    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }

    // 1. Pre-compute all distances
    std::vector<std::vector<long long>> dist_matrix(n, std::vector<long long>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dist_matrix[i][j] = dist_matrix[j][i] = calc_dist(points[i], points[j]);
        }
    }

    // 2. Generate Initial Tour (using GreedyTour/Naive)
    std::vector<int> tour(n);
    std::vector<bool> used(n, false);
    tour[0] = 0;
    used[0] = true;
    for (int i = 1; i < n; ++i) {
        int best = -1;
        long long min_dist = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j]) {
                long long d = dist_matrix[tour[i - 1]][j];
                if (best == -1 || d < min_dist) {
                    min_dist = d;
                    best = j;
                }
            }
        }
        tour[i] = best;
        used[best] = true;
    }

    // 3. Simulated Annealing
    clock_t start_time = clock();
    // Set time limit (e.g., 1.8s for a 2s limit)
    double time_limit = (n > 500) ? 1.8 : 0.8; 

    double T = 10000.0;
    double cooling_rate = 0.9999995;

    std::vector<int> best_tour = tour;
    long long best_cost = calc_tour_length(tour, n, dist_matrix);
    long long current_cost = best_cost;

    while ((double)(clock() - start_time) / CLOCKS_PER_SEC < time_limit) {
        // Pick two random points to swap (2-opt)
        int i = rand() % n;
        int j = rand() % n;
        if (i == j) continue;
        if (i > j) std::swap(i, j);

        // Get the nodes *before* and *after* the segment to be reversed
        int i_prev = (i == 0) ? n - 1 : i - 1;
        int j_next = (j == n - 1) ? 0 : (j + 1) % n;

        int city_i = tour[i];
        int city_j = tour[j];
        int city_i_prev = tour[i_prev];
        int city_j_next = tour[j_next];

        // Calculate cost change in O(1)
        long long old_edges = dist_matrix[city_i_prev][city_i] + dist_matrix[city_j][city_j_next];
        long long new_edges = dist_matrix[city_i_prev][city_j] + dist_matrix[city_i][city_j_next];
        long long delta_cost = new_edges - old_edges;

        // Acceptance criteria
        if (delta_cost < 0 || (T > 0.001 && (double)rand() / RAND_MAX < exp(-delta_cost / T))) {
            // Accept the move: reverse the segment
            std::reverse(tour.begin() + i, tour.begin() + j + 1);
            current_cost += delta_cost;

            if (current_cost < best_cost) {
                best_cost = current_cost;
                best_tour = tour;
            }
        }
        T *= cooling_rate;
    }

    // 4. Output the best tour found
    for (int i = 0; i < n; ++i) {
        std::cout << best_tour[i] << "\n";
    }

    return 0;
}