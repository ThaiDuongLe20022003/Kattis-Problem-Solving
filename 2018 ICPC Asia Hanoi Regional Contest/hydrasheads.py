INF = 1 << 29
memo = {}

def solve(h, t):
    """
    Find minimum moves to kill hydra with h heads and t tails
    """
    if (h, t) in memo:
        return memo[(h, t)]
    
    best = INF
    
    # Move 2: Cut 1 tail → 2 new tails grow (only use in small states)
    if h <= 2 and t <= 2:
        best = min(best, solve(h, t + 1))
    
    # Move 4: Cut 2 tails → 1 new head grows
    if t >= 2:
        best = min(best, solve(h + 1, t - 2))
    
    # Move 3: Cut 2 heads → nothing grows
    if h >= 2:
        best = min(best, solve(h - 2, t))
    
    best += 1
    memo[(h, t)] = best
    return best

def main():
    # Initialize base cases
    memo[(1, 0)] = INF  # Impossible
    memo[(0, 0)] = 0    # Already dead
    memo[(2, 0)] = 1    # Cut 2 heads
    memo[(1, 2)] = 2
    memo[(0, 4)] = 3
    
    while True:
        line = input().strip()
        h, t = map(int, line.split())
        
        if h == 0 and t == 0:
            break
        
        result = solve(h, t)
        if result == INF:
            print(-1)
        else:
            print(result)

if __name__ == "__main__":
    main()