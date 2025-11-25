#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    if (!(std::cin >> n)) {
        return 0;
    }

    std::vector<int> p(n);
    std::vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> p[i])) {
            return 0;
        }
        pos[p[i]] = i;
    }

    int num_blocks = 0;
    int last_pos = -1; 

    for (int card = 1; card <= n; ++card) {
        int current_pos = pos[card];
        if (current_pos < last_pos) {
            num_blocks++;
        }
        last_pos = current_pos;
    }

    num_blocks++;

    int result = 0;
    int power_of_2 = 1;
    while (power_of_2 < num_blocks) {
        power_of_2 *= 2;
        result++;
    }

    std::cout << result << "\n";

    return 0;
}