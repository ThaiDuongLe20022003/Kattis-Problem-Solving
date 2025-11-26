times = int(input())

for i in range(times):
    s = input()
    
    if s.startswith("Simon says"):
        result = s[11:]
        print(result)