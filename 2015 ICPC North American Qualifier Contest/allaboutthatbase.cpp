#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

using namespace std;

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
// Returns -1 if the number is too large (overflow) or invalid for the base.
long long to_decimal(const string& num_str, int base) {
    if (base == 1) {
        // Unary base: value is the number of '1's.
        // The problem states unary uses '1' rather than '0'.
        // All digits must be '1'.
        for (char c : num_str) {
            if (c != '1') return -1;
        }
        // Check for overflow: 2^32 - 1 is the limit.
        if (num_str.length() > 32) return -1;
        return num_str.length();
    }

    long long value = 0;
    long long max_val = (1LL << 32) - 1; // 2^32 - 1

    for (char c : num_str) {
        int digit_val = char_to_val(c);

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

    // The problem states operands must be in the decimal range [1, 2^32 - 1].
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

void solve() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return;

    string line;
    getline(cin, line); // Consume the rest of the first line

    while (N--) {
        getline(cin, line);
        stringstream ss(line);
        
        string X_str, Y_str, Z_str, op_str, eq_str;
        ss >> X_str >> op_str >> Y_str >> eq_str >> Z_str;

        char op = op_str[0];
        
        string valid_bases = "";

        // Iterate over all possible bases from 1 to 36
        for (int B = 1; B <= 36; ++B) {
            long long X_val = to_decimal(X_str, B);
            long long Y_val = to_decimal(Y_str, B);
            long long Z_val = to_decimal(Z_str, B);

            // Check if all operands are valid in base B and within the range [1, 2^32 - 1]
            if (X_val == -1 || Y_val == -1 || Z_val == -1) {
                continue;
            }

            long long result = 0;
            bool overflow = false;
            long long max_val = (1LL << 32) - 1;

            // Perform the operation and check for overflow
            switch (op) {
                case '+':
                    if (X_val > max_val - Y_val) {
                        overflow = true;
                    } else {
                        result = X_val + Y_val;
                    }
                    break;
                case '-':
                    result = X_val - Y_val;
                    break;
                case '*':
                    if (X_val > max_val / Y_val) {
                        overflow = true;
                    } else {
                        result = X_val * Y_val;
                    }
                    break;
                case '/':
                    if (Y_val == 0) {
                        // Division by zero is invalid
                        continue;
                    }
                    // The result of division must be a whole number, and the problem implies integer division.
                    // The expression is X op Y = Z. So X / Y must equal Z exactly.
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
                    valid_bases += base_to_symbol(B);
                }
            }
        }

        // Output the result
        if (valid_bases.empty()) {
            cout << "invalid\n";
        } else {
            cout << valid_bases << "\n";
        }
    }
}

int main() {
    solve();
    return 0;
}