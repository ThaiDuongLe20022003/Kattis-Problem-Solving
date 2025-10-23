#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip> // For setprecision

using namespace std;

// Use long long for coordinates to prevent overflow in intermediate calculations
using ll = long long;

struct Point {
    ll x, y;

    // Sort by x, then y
    bool operator<(const Point& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

// --- Geometry Helper Functions ---

// 2D cross product of vectors (p->a) and (p->b)
// Returns > 0 for a left turn, 0 for collinear, < 0 for a right turn
ll cross_product(Point p, Point a, Point b) {
    return (a.x - p.x) * (b.y - p.y) - (a.y - p.y) * (b.x - p.x);
}

// Squared Euclidean distance. We avoid sqrt until the very end.
ll dist_sq(Point a, Point b) {
    ll dx = a.x - b.x;
    ll dy = a.y - b.y;
    return dx * dx + dy * dy;
}

// --- Main Algorithm ---

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int C;
    cin >> C;

    vector<Point> points(C);
    for (int i = 0; i < C; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // 1. Find the Convex Hull (Monotone Chain)
    
    // Sort points lexicographically
    sort(points.begin(), points.end());

    vector<Point> hull;

    // Build lower hull
    for (const auto& p : points) {
        while (hull.size() >= 2 && cross_product(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // Build upper hull
    // We remove the last point to avoid duplication with the start of the upper hull
    hull.pop_back(); 
    size_t lower_hull_size = hull.size();
    
    for (int i = C - 1; i >= 0; --i) {
        const auto& p = points[i];
        while (hull.size() > lower_hull_size + 1 && cross_product(hull[hull.size() - 2], hull.back(), p) <= 0) {
            hull.pop_back();
        }
        hull.push_back(p);
    }

    // Remove the last point (which is the same as the first)
    hull.pop_back();

    // Handle edge case: all points are collinear
    if (hull.size() < 2) {
        if (C < 2) {
            cout << "0.0" << endl;
        } else {
            // All points were collinear, max dist is between first and last
            cout << fixed << setprecision(10) << sqrt(dist_sq(points[0], points[C-1])) << endl;
        }
        return 0;
    }

    // 2. Find Diameter (Rotating Calipers)
    
    ll max_dist_sq = 0;
    int h = hull.size();
    
    // `j` is the antipodal (farthest) point from the edge (i, i+1)
    for (int i = 0, j = 1; i < h; ++i) {
        int next_i = (i + 1) % h;
        
        // Move `j` forward until it's farthest from the edge (i, next_i)
        // We do this by comparing the "area" of the triangle (i, next_i, j)
        // with (i, next_i, j+1).
        while (abs(cross_product(hull[i], hull[next_i], hull[j])) < abs(cross_product(hull[i], hull[next_i], hull[(j + 1) % h]))) {
            j = (j + 1) % h;
        }

        // The max distance must be from one of the edge's endpoints (i or next_i)
        // to the antipodal point j.
        max_dist_sq = max(max_dist_sq, dist_sq(hull[i], hull[j]));
        max_dist_sq = max(max_dist_sq, dist_sq(hull[next_i], hull[j]));
    }

    // 3. Output
    // Print the final answer with high precision
    cout << fixed << setprecision(10) << sqrt((long double)max_dist_sq) << endl;

    return 0;
}