n,m = [int(i) for i in input().split(" ")]
src = dict()
for i in range(n):
    t = input().replace(" ","").split("->")
    src[t[0]] = t[1]
s = input()
for i in range(m):
    temp = ""
    for c in s:
        if c in src:
            temp += src[c]
        else:
            temp += c
    s = temp
print(s)