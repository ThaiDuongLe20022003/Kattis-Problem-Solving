#include <iostream>
#include <vector>
#include <numeric> // For std::iota
#include <string>

// DSU 'parent' array
std::vector<int> parent;
// 'size' array for union-by-size optimization
std::vector<int> dsu_size;

/**
 * Finds the representative (root) of the set containing element i.
 * Uses path compression for optimization.
 */
int find_root(int i) {
    if (parent[i] == i)
        return i;
    // Path compression
    return parent[i] = find_root(parent[i]); 
}

/**
 * Unites the sets containing elements i and j.
 * Uses union-by-size for optimization.
 */
void unite_sets(int i, int j) {
    int root_i = find_root(i);
    int root_j = find_root(j);
    if (root_i != root_j) {
        // Union-by-size: attach smaller tree to larger tree
        if (dsu_size[root_i] < dsu_size[root_j])
            std::swap(root_i, root_j);
        parent[root_j] = root_i;
        dsu_size[root_i] += dsu_size[root_j];
    }
}

int main() {
    // 1. --- FAST I/O ---
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    // 2. --- Read Balances ---
    // Use long long to prevent overflow during summation
    std::vector<long long> balances(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> balances[i];
    }

    // 3. --- Initialize DSU ---
    parent.resize(n);
    std::iota(parent.begin(), parent.end(), 0); // Fills parent[i] = i
    dsu_size.assign(n, 1); // Each set starts with size 1

    // 4. --- Process Friendships (Union) ---
    for (int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        unite_sets(x, y);
    }

    // 5. --- Sum Balances per Component ---
    // Add each node's balance to its component's root
    for (int i = 0; i < n; ++i) {
        if (parent[i] != i) { // If i is not a root
            // Find the root and add this balance to it
            balances[find_root(i)] += balances[i];
        }
    }

    // 6. --- Check Component Sums ---
    // Only the root nodes now hold the total sum for their component
    for (int i = 0; i < n; ++i) {
        if (parent[i] == i) { // If i is a root
            if (balances[i] != 0) {
                std::cout << "IMPOSSIBLE\n";
                return 0;
            }
        }
    }

    // 7. --- If all root sums are 0 ---
    std::cout << "POSSIBLE\n";
    return 0;
}