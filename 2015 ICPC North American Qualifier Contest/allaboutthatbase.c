#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function to convert a character symbol to its decimal value
int char_to_val(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    return -1; // Should not happen
}

// Function to convert a number string from a given base to a long long decimal value
long long to_decimal(const char* num_str, int base) {
    if (base == 1) {
        // Unary base: value is the number of '1's
        for (int i = 0; num_str[i] != '\0'; i++) {
            if (num_str[i] != '1') return -1;
        }
        // Check for overflow: 2^32 - 1 is the limit
        if (strlen(num_str) > 32) return -1;
        return strlen(num_str);
    }

    long long value = 0;
    long long max_val = (1LL << 32) - 1; // 2^32 - 1

    for (int i = 0; num_str[i] != '\0'; i++) {
        int digit_val = char_to_val(num_str[i]);

        // Check if the digit is valid for the base
        if (digit_val >= base) {
            return -1;
        }

        // Check for overflow before multiplication
        if (value > max_val / base) {
            return -1;
        }

        value = value * base + digit_val;

        // Check for overflow after addition
        if (value > max_val) {
            return -1;
        }
    }

    // The problem states operands must be in the decimal range [1, 2^32 - 1]
    if (value == 0) return -1;

    return value;
}

// Function to convert a base number (1-36) to its output symbol
char base_to_symbol(int base) {
    if (base >= 1 && base <= 9) {
        return base + '0';
    } else if (base >= 10 && base <= 35) {
        return base - 10 + 'a';
    } else if (base == 36) {
        return '0';
    }
    return '?'; // Should not happen
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    getchar(); // Consume newline

    char line[1000];
    
    for (int case_num = 0; case_num < N; case_num++) {
        if (fgets(line, sizeof(line), stdin) == NULL) break;
        
        char X_str[100], Y_str[100], Z_str[100], op_str[10];
        if (sscanf(line, "%s %s %s = %s", X_str, op_str, Y_str, Z_str) != 4) {
            printf("invalid\n");
            continue;
        }
        
        char op = op_str[0];
        char valid_bases[37] = ""; // 36 bases + null terminator
        int valid_count = 0;

        // Iterate over all possible bases from 1 to 36
        for (int B = 1; B <= 36; B++) {
            long long X_val = to_decimal(X_str, B);
            long long Y_val = to_decimal(Y_str, B);
            long long Z_val = to_decimal(Z_str, B);

            // Check if all operands are valid in base B and within the range [1, 2^32 - 1]
            if (X_val == -1 || Y_val == -1 || Z_val == -1) {
                continue;
            }

            long long result = 0;
            int overflow = 0;
            long long max_val = (1LL << 32) - 1;

            // Perform the operation and check for overflow
            switch (op) {
                case '+':
                    if (X_val > max_val - Y_val) {
                        overflow = 1;
                    } else {
                        result = X_val + Y_val;
                    }
                    break;
                case '-':
                    result = X_val - Y_val;
                    break;
                case '*':
                    if (X_val > max_val / Y_val) {
                        overflow = 1;
                    } else {
                        result = X_val * Y_val;
                    }
                    break;
                case '/':
                    if (Y_val == 0) {
                        // Division by zero is invalid
                        continue;
                    }
                    // Check for exact division
                    if (X_val % Y_val != 0) {
                        continue;
                    }
                    result = X_val / Y_val;
                    break;
            }

            // Check if the result is valid and matches Z_val
            if (!overflow && result == Z_val) {
                // The result must also be in the range [1, 2^32 - 1]
                if (result >= 1 && result <= max_val) {
                    valid_bases[valid_count++] = base_to_symbol(B);
                }
            }
        }

        // Output the result
        if (valid_count == 0) {
            printf("invalid\n");
        } else {
            valid_bases[valid_count] = '\0';
            printf("%s\n", valid_bases);
        }
    }

    return 0;
}