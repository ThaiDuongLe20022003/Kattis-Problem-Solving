#include <iostream>
#include <string>
#include <algorithm> // For std::min

int main() {
    // 1. Use fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;
    std::string s;
    std::cin >> s;

    // 2. Check for Cost 0
    // Pattern: "lv"
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == 'l' && s[i + 1] == 'v') {
            std::cout << 0 << "\n";
            return 0;
        }
    }

    // 3. Check for Cost 1

    // Case 1A: 1-Edit
    // Pattern: "l*" or "*v"
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == 'l' || s[i + 1] == 'v') {
            std::cout << 1 << "\n";
            return 0;
        }
    }

    // Case 1B: 1-Reverse
    // Pattern: "vl"
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == 'v' && s[i + 1] == 'l') {
            std::cout << 1 << "\n";
            return 0;
        }
    }

    // Case 1C: 1-Reverse (Optimized O(N) check)
    // Pattern: "l...v" (with at least one char in between)
    int min_l_index = n + 1; // Sentinel value (larger than any possible index)
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'l') {
            min_l_index = std::min(min_l_index, i);
        }
        
        // If we find a 'v', check if it's at least 2 spots
        // after the earliest 'l' we've seen so far.
        if (s[i] == 'v') {
            if (i >= min_l_index + 2) {
                std::cout << 1 << "\n";
                return 0;
            }
        }
    }

    // 4. Check for Cost 2
    // If we haven't returned 0 or 1, the answer must be 2.
    std::cout << 2 << "\n";

    return 0;
}