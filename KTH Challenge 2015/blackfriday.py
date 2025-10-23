n = int(input())
rolls = list(map(int, input().split()))

freq = [0] * 7  # index 0 unused, 1..6 used

for r in rolls:
    freq[r] += 1

winner = -1
for outcome in range(6, 0, -1):
    if freq[outcome] == 1:
        # find who has this outcome
        for i in range(n):
            if rolls[i] == outcome:
                winner = i + 1
                break
        break

if winner == -1:
    print("none")
else:
    print(winner)