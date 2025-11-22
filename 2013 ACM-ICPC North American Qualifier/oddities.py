n = int(input())

for i in range(n):
    next_num = int(input())
    
    if next_num & 1 == 1:
        print(f"{next_num} is odd")
    else:
        print(f"{next_num} is even")