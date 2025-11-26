import math

def combinations(n, k):
    if k < 0 or k > n:
        return 0
    if k == 0 or k == n:
        return 1
    if k > n // 2:
        k = n - k
    
    res = 1.0
    for i in range(1, k + 1):
        res = res * (n - i + 1) / i
    return res

def main():
    N_cases = int(input())
    
    for _ in range(N_cases):
        R, S, X, Y, W = map(int, input().split())
        
        # Calculate probability of a single successful roll
        p_success = 0.0
        if R <= S:
            p_success = (S - R + 1) / S
        
        p_failure = 1.0 - p_success
        
        # Calculate probability of winning the bet
        P_win = 0.0
        for k in range(X, Y + 1):
            nCk = combinations(Y, k)
            p_succ_k = p_success ** k
            p_fail_Y_k = p_failure ** (Y - k)
            P_win += nCk * p_succ_k * p_fail_Y_k
        
        # Calculate expected return and output result
        E_return = P_win * W
        if E_return > 1.0:
            print("yes")
        else:
            print("no")

if __name__ == "__main__":
    main()