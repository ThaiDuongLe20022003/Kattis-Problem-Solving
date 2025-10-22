#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath> // For ceil

// Points table (index 0 is unused, index 1 is Rank 1, ...)
// Ranks > 30 get 0 points.
int points[] = {
    0, 100, 75, 60, 50, 45, 40, 36, 32, 29, 26, 
    24, 22, 20, 18, 16, 15, 14, 13, 12, 11, 
    10, 9, 8, 7, 6, 5, 4, 3, 2, 1
};
const int MAX_RANK_WITH_POINTS = 30;

struct Contestant {
    int p, f, o, extra_points;
    int original_index;
    int score;

    /**
     * Helper to get base points for a given rank.
     */
    static int get_base_points(int rank) {
        if (rank > MAX_RANK_WITH_POINTS) {
            return 0;
        }
        return points[rank];
    }
};

/**
 * Comparison function for sorting by ACM contest rank.
 * Returns true if 'a' comes before 'b'.
 */
bool compareByRank(const Contestant& a, const Contestant& b) {
    if (a.p != b.p) return a.p > b.p; // More problems first
    if (a.f != b.f) return a.f < b.f; // Less penalty second
    if (a.o != b.o) return a.o < b.o; // Earlier submission third
    return false; // Tied
}

/**
 * Checks if two contestants are tied (identical p, f, o).
 */
bool areTied(const Contestant& a, const Contestant& b) {
    return a.p == b.p && a.f == b.f && a.o == b.o;
}

/**
 * Comparison function for sorting back to the original input order.
 */
bool compareByIndex(const Contestant& a, const Contestant& b) {
    return a.original_index < b.original_index;
}

int main() {
    // Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<Contestant> contestants(n);
    for (int i = 0; i < n; ++i) {
        contestants[i].original_index = i;
        std::cin >> contestants[i].p 
                 >> contestants[i].f 
                 >> contestants[i].o 
                 >> contestants[i].extra_points;
    }

    // 1. Sort by ACM ranking rules
    std::sort(contestants.begin(), contestants.end(), compareByRank);

    // 2. Assign scores, handling ties
    for (int i = 0; i < n; /* i is incremented inside */) {
        // Find the end of the tied group
        int j = i;
        while (j + 1 < n && areTied(contestants[i], contestants[j + 1])) {
            j++;
        }

        // Now, contestants from i to j (inclusive) are tied
        int num_tied = j - i + 1;
        double total_base_score = 0;

        // Sum the base scores for the ranks they occupy
        for (int k = 0; k < num_tied; ++k) {
            int rank = i + 1 + k; // Their ranks are i+1, i+2, ...
            total_base_score += Contestant::get_base_points(rank);
        }

        // Calculate the average and round up (ceil), as per the sample's ceil symbol
        int final_base_score = (int)std::ceil(total_base_score / num_tied);

        // Assign this score + extra points to everyone in the group
        for (int k = i; k <= j; ++k) {
            contestants[k].score = final_base_score + contestants[k].extra_points;
        }

        // Move to the next group
        i = j + 1;
    }

    // 3. Sort back to original order
    std::sort(contestants.begin(), contestants.end(), compareByIndex);

    // 4. Print results
    for (int i = 0; i < n; ++i) {
        std::cout << contestants[i].score << "\n";
    }

    return 0;
}