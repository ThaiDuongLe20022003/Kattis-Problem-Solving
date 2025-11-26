import java.util.Scanner;

public class allaboutthatbase {
    // Function to convert a character symbol to its decimal value
    static int charToVal(char c) {
        if (c >= '0' && c <= '9') {
            return c - '0';
        } else if (c >= 'a' && c <= 'z') {
            return c - 'a' + 10;
        }
        return -1; // Should not happen
    }

    // Function to convert a number string from a given base to a long decimal value
    static long toDecimal(String numStr, int base) {
        if (base == 1) {
            // Unary base: value is the number of '1's
            for (int i = 0; i < numStr.length(); i++) {
                if (numStr.charAt(i) != '1') return -1;
            }
            // Check for overflow: 2^32 - 1 is the limit
            if (numStr.length() > 32) return -1;
            return numStr.length();
        }

        long value = 0;
        long maxVal = (1L << 32) - 1; // 2^32 - 1

        for (int i = 0; i < numStr.length(); i++) {
            char c = numStr.charAt(i);
            int digitVal = charToVal(c);

            // Check if the digit is valid for the base
            if (digitVal >= base) {
                return -1;
            }

            // Check for overflow before multiplication
            if (value > maxVal / base) {
                return -1;
            }

            value = value * base + digitVal;

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
    static char baseToSymbol(int base) {
        if (base >= 1 && base <= 9) {
            return (char)(base + '0');
        } else if (base >= 10 && base <= 35) {
            return (char)(base - 10 + 'a');
        } else if (base == 36) {
            return '0';
        }
        return '?'; // Should not happen
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int N = Integer.parseInt(scanner.nextLine());
        
        for (int caseNum = 0; caseNum < N; caseNum++) {
            String line = scanner.nextLine();
            String[] parts = line.split(" ");
            
            if (parts.length < 5) {
                System.out.println("invalid");
                continue;
            }

            String XStr = parts[0];
            String opStr = parts[1];
            String YStr = parts[2];
            String ZStr = parts[4]; // parts[3] is "="
            
            char op = opStr.charAt(0);
            StringBuilder validBases = new StringBuilder();

            // Iterate over all possible bases from 1 to 36
            for (int B = 1; B <= 36; B++) {
                long XVal = toDecimal(XStr, B);
                long YVal = toDecimal(YStr, B);
                long ZVal = toDecimal(ZStr, B);

                // Check if all operands are valid in base B
                if (XVal == -1 || YVal == -1 || ZVal == -1) {
                    continue;
                }

                long result = 0;
                boolean overflow = false;
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
                        validBases.append(baseToSymbol(B));
                    }
                }
            }

            // Output the result
            if (validBases.length() == 0) {
                System.out.println("invalid");
            } else {
                System.out.println(validBases.toString());
            }
        }
        
        scanner.close();
    }
}