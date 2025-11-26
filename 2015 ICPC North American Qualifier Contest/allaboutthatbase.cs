using System;
using System.Text;

class Program {
    // Function to convert a character symbol to its decimal value
    static int CharToVal(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'a' && c <= 'z') {
            return c - 'a' + 10;
        }
        return -1; // Should not happen
    }

    // Function to convert a number string from a given base to a long decimal value
    static long ToDecimal(string numStr, int baseVal) {
        if (baseVal == 1) {
            // Unary base: value is the number of '1's
            foreach (char c in numStr) {
                if (c != '1') return -1;
            }
            // Check for overflow: 2^32 - 1 is the limit
            if (numStr.Length > 32) return -1;
            return numStr.Length;
        }

        long value = 0;
        long maxVal = (1L << 32) - 1; // 2^32 - 1

        foreach (char c in numStr) {
            int digitVal = CharToVal(c);

            // Check if the digit is valid for the base
            if (digitVal >= baseVal) {
                return -1;
            }

            // Check for overflow before multiplication
            if (value > maxVal / baseVal) {
                return -1;
            }

            value = value * baseVal + digitVal;

            // Check for overflow after addition
            if (value > maxVal) {
                return -1;
            }
        }

        // The problem states operands must be in the decimal range [1, 2^32 - 1]
        if (value == 0) return -1;

        return value;
    }

    // Function to convert a base number (1-36) to its output symbol
    static char BaseToSymbol(int baseVal) {
        if (baseVal >= 1 && baseVal <= 9) {
            return (char)(baseVal + '0');
        } else if (baseVal >= 10 && baseVal <= 35) {
            return (char)(baseVal - 10 + 'a');
        } else if (baseVal == 36) {
            return '0';
        }
        return '?'; // Should not happen
    }

    static void Main() {
        int N = int.Parse(Console.ReadLine());
        
        for (int caseNum = 0; caseNum < N; caseNum++) {
            string line = Console.ReadLine();
            string[] parts = line.Split(' ');
            
            if (parts.Length < 5) {
                Console.WriteLine("invalid");
                continue;
            }

            string XStr = parts[0];
            string opStr = parts[1];
            string YStr = parts[2];
            string ZStr = parts[4]; // parts[3] is "="
            
            char op = opStr[0];
            StringBuilder validBases = new StringBuilder();

            // Iterate over all possible bases from 1 to 36
            for (int B = 1; B <= 36; B++) {
                long XVal = ToDecimal(XStr, B);
                long YVal = ToDecimal(YStr, B);
                long ZVal = ToDecimal(ZStr, B);

                // Check if all operands are valid in base B
                if (XVal == -1 || YVal == -1 || ZVal == -1) {
                    continue;
                }

                long result = 0;
                bool overflow = false;
                long maxVal = (1L << 32) - 1;

                // Perform the operation and check for overflow
                switch (op) {
                    case '+':
                        if (XVal > maxVal - YVal) {
                            overflow = true;
                        } else {
                            result = XVal + YVal;
                        }
                        break;
                    case '-':
                        result = XVal - YVal;
                        break;
                    case '*':
                        if (XVal > maxVal / YVal) {
                            overflow = true;
                        } else {
                            result = XVal * YVal;
                        }
                        break;
                    case '/':
                        if (YVal == 0) {
                            continue;
                        }
                        if (XVal % YVal != 0) {
                            continue;
                        }
                        result = XVal / YVal;
                        break;
                }

                // Check if the result is valid and matches ZVal
                if (!overflow && result == ZVal) {
                    if (result >= 1 && result <= maxVal) {
                        validBases.Append(BaseToSymbol(B));
                    }
                }
            }

            // Output the result
            if (validBases.Length == 0) {
                Console.WriteLine("invalid");
            } else {
                Console.WriteLine(validBases.ToString());
            }
        }
    }
}