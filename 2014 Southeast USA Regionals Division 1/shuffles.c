#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// The problem constraints are N <= 1,000,000.
// We need to use fast I/O and efficient data structures.
// The core logic is to count the number of "runs" or blocks in the final permutation.

int main() {
    // Fast I/O is less critical in C than C++ but good practice.
    // We will rely on standard scanf/printf which are generally fast enough.
    int n;
    
    // Kattis problems often test with multiple test cases, but the problem
    // description suggests a single test case per run. A single read is safer
    // for a simple C program unless explicitly told otherwise.
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    // p is the final permutation (not strictly needed for the logic, but for reading input)
    // pos[c] stores the index of card 'c' in the shuffled deck.
    // Card values are 1 to n, so we need size n+1.
    // Since n can be up to 1,000,000, we must use dynamic allocation.
    // Using int for pos is fine as indices are up to 1,000,000.
    int *pos = (int *)malloc((n + 1) * sizeof(int));
    if (pos == NULL) {
        // Handle memory allocation failure
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        int card;
        if (scanf("%d", &card) != 1) {
            free(pos);
            return 0;
        }
        pos[card] = i;
    }

    int num_blocks = 0;
    int last_pos = -1; // Position of the last card (card - 1) placed in the current block

    // Iterate through the cards in their original sorted order (1, 2, ..., n)
    for (int card = 1; card <= n; ++card) {
        int current_pos = pos[card];
        
        // If the current card's position is less than the last card's position,
        // it means this card must start a new block.
        if (current_pos < last_pos) {
            num_blocks++;
        }
        last_pos = current_pos;
    }

    // The loop counts the number of times a new block *starts*.
    // The first block is not counted in the loop, so we add 1.
    num_blocks++;

    // The minimum number of shuffles 'k' is the smallest integer such that 2^k >= num_blocks.
    int result = 0;
    int power_of_2 = 1;
    while (power_of_2 < num_blocks) {
        // We must be careful with integer overflow if num_blocks was larger,
        // but since num_blocks <= n+1 <= 1,000,001, the power_of_2 will not
        // exceed 2^20 (1,048,576), which is safe for a standard 32-bit int.
        power_of_2 *= 2;
        result++;
    }

    printf("%d\n", result);

    free(pos);
    return 0;
}