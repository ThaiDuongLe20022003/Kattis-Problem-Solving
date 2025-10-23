from math import sqrt
t = int(input())
ps = []
for i in range(t):
    ps.append([float(c) for c in input().split(" ")])
tarea = int(input())
carea = 0
for i in range(t):
    n = (i+1)%len(ps)
    carea += ps[i][0]*ps[n][1] - ps[i][1]*ps[n][0]
carea = carea/2
inc = sqrt(abs(tarea/carea))

for i in range(len(ps)):
    for j in range(2):
        ps[i][j] *= inc

sX = ps[0][0]
for i in ps:
    sX = min(sX,i[0])
sX = -sX
sY = ps[0][1]
for i in ps:
    sY = min(sY,i[1])
sY = -sY

for i in range(len(ps)):
    print(ps[i][0]+sX,ps[i][1]+sY)