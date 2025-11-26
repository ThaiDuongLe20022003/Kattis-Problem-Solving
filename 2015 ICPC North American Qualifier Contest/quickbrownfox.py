n = int(input())

for i in range(n):
    letters = [False] * 26
    s = input()
    used = 0
    
    for c in s:
        temp = ord(c.lower()) - ord('a')
        if 0 <= temp < 26 and not letters[temp]:
            letters[temp] = True
            used += 1
    
    if used == 26:
        print("pangram", end="")
    else:
        print("missing ", end="")
        for j in range(26):
            if not letters[j]:
                print(chr(j + ord('a')), end="")
    
    print()