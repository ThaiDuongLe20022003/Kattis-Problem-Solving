def char_to_val(c):
    if '0' <= c <= '9':
        return ord(c) - ord('0')
    elif 'a' <= c <= 'z':
        return ord(c) - ord('a') + 10
    return -1  # Should not happen

def to_decimal(num_str, base):
    if base == 1:
        # Unary base: value is the number of '1's
        if any(c != '1' for c in num_str):
            return -1
        # Check for overflow: 2^32 - 1 is the limit
        if len(num_str) > 32:
            return -1
        return len(num_str)
    
    value = 0
    max_val = (1 << 32) - 1  # 2^32 - 1
    
    for c in num_str:
        digit_val = char_to_val(c)
        
        # Check if the digit is valid for the base
        if digit_val >= base:
            return -1
        
        # Check for overflow before multiplication
        if value > max_val // base:
            return -1
        
        value = value * base + digit_val
        
        # Check for overflow after addition
        if value > max_val:
            return -1
    
    # The problem states operands must be in the decimal range [1, 2^32 - 1]
    if value == 0:
        return -1
    
    return value

def base_to_symbol(base):
    if 1 <= base <= 9:
        return str(base)
    elif 10 <= base <= 35:
        return chr(ord('a') + base - 10)
    elif base == 36:
        return '0'
    return '?'  # Should not happen

def main():
    import sys
    data = sys.stdin.read().splitlines()
    N = int(data[0])
    
    for i in range(1, N + 1):
        line = data[i].strip()
        parts = line.split()
        
        if len(parts) < 5:
            print("invalid")
            continue
            
        X_str = parts[0]
        op_str = parts[1]
        Y_str = parts[2]
        Z_str = parts[4]  # parts[3] is "="
        
        op = op_str[0]
        valid_bases = []
        
        # Iterate over all possible bases from 1 to 36
        for B in range(1, 37):
            X_val = to_decimal(X_str, B)
            Y_val = to_decimal(Y_str, B)
            Z_val = to_decimal(Z_str, B)
            
            # Check if all operands are valid in base B
            if X_val == -1 or Y_val == -1 or Z_val == -1:
                continue
                
            max_val = (1 << 32) - 1
            overflow = False
            result = 0
            
            # Perform the operation and check for overflow
            if op == '+':
                if X_val > max_val - Y_val:
                    overflow = True
                else:
                    result = X_val + Y_val
            elif op == '-':
                result = X_val - Y_val
            elif op == '*':
                if X_val > max_val // Y_val:
                    overflow = True
                else:
                    result = X_val * Y_val
            elif op == '/':
                if Y_val == 0:
                    continue
                if X_val % Y_val != 0:
                    continue
                result = X_val // Y_val
            
            # Check if the result is valid and matches Z_val
            if not overflow and result == Z_val:
                if 1 <= result <= max_val:
                    valid_bases.append(base_to_symbol(B))
        
        # Output the result
        if not valid_bases:
            print("invalid")
        else:
            print(''.join(valid_bases))

if __name__ == "__main__":
    main()