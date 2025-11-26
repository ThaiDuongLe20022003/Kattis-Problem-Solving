import math

testcases = int(input())

for zaxbys in range(testcases):
    str_input = input()
    
    i = 1
    length = len(str_input)
    
    while i * i < length:
        i += 1
    
    # Pad string with asterisks
    padded_str = str_input + '*' * (i * i - length)
    
    # Create 2D list
    nums = [['' for _ in range(i)] for _ in range(i)]
    
    # Fill 2D list
    for r in range(i):
        for c in range(i):
            nums[r][c] = padded_str[i * r + c]
    
    # Output result
    for c in range(i):
        for r in range(i-1, -1, -1):
            if nums[r][c] != '*':
                print(nums[r][c], end='')
    
    print()