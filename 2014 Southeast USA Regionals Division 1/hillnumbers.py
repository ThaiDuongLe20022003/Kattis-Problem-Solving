def is_hill_number(s):
    if not s or all(c == '0' for c in s):
        return False
    
    falling = False
    for i in range(len(s) - 1):
        if s[i] < s[i + 1]:
            if falling:
                return False
        elif s[i] > s[i + 1]:
            falling = True
    return True

def solve(n_str):
    S = n_str
    memo = {}
    
    def dp(pos, prev_d, is_less, is_started, is_falling):
        if pos == len(S):
            return 1 if is_started else 0
            
        key = (pos, prev_d, is_less, is_started, is_falling)
        if key in memo:
            return memo[key]
            
        ans = 0
        upper_bound = 9 if is_less else int(S[pos])
        
        for d in range(upper_bound + 1):
            if not is_started:
                if d == 0:
                    ans += dp(pos + 1, 0, True, False, False)
                else:
                    ans += dp(pos + 1, d, is_less or (d < upper_bound), True, False)
            else:
                if is_falling:
                    if d <= prev_d:
                        ans += dp(pos + 1, d, is_less or (d < upper_bound), True, True)
                else:
                    if d < prev_d:
                        ans += dp(pos + 1, d, is_less or (d < upper_bound), True, True)
                    else:
                        ans += dp(pos + 1, d, is_less or (d < upper_bound), True, False)
        
        memo[key] = ans
        return ans
    
    return dp(0, 0, False, False, False)

def main():
    import sys
    for line in sys.stdin:
        n_str = line.strip()
        if not n_str:
            continue
        if not is_hill_number(n_str):
            print(-1)
        else:
            print(solve(n_str))

if __name__ == "__main__":
    main()