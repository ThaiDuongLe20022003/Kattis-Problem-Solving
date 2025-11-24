import math
import sys

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y

def euclidean_dist(a, b):
    return math.sqrt((a.x - b.x) ** 2 + (a.y - b.y) ** 2)

def linear_program_solution(A, b, c):
    m = len(b)
    n = len(c)
    
    tableau = [[0.0] * (n + 2) for _ in range(m + 2)]
    basic = [0] * m
    non_basic = [0] * (n + 1)
    
    # Initialize tableau
    for i in range(m):
        for j in range(n):
            tableau[i][j] = A[i][j]
        basic[i] = n + i
        tableau[i][n] = -1
        tableau[i][n + 1] = b[i]
    
    for j in range(n + 1):
        non_basic[j] = j
    non_basic[n] = -1
    
    for j in range(n):
        tableau[m][j] = -c[j]
    tableau[m + 1][n] = 1
    
    def pivot(row, col):
        inv = 1.0 / tableau[row][col]
        
        for i in range(m + 2):
            if i != row and abs(tableau[i][col]) > 1e-8:
                temp = tableau[i][col] * inv
                for j in range(n + 2):
                    tableau[i][j] -= tableau[row][j] * temp
                tableau[i][col] = tableau[row][col] * temp
        
        for i in range(m + 2):
            if i != row:
                tableau[i][col] *= -inv
        
        for j in range(n + 2):
            if j != col:
                tableau[row][j] *= inv
        tableau[row][col] = inv
        
        basic[row], non_basic[col] = non_basic[col], basic[row]
    
    def simplex(phase):
        while True:
            r = m + (1 if phase == 1 else 0)
            col = -1
            
            for j in range(n + 1):
                if phase == 2 and non_basic[j] == -1:
                    continue
                if col == -1 or tableau[r][j] < tableau[r][col] - 1e-8 or (
                    abs(tableau[r][j] - tableau[r][col]) < 1e-8 and non_basic[j] < non_basic[col]):
                    col = j
            
            if tableau[r][col] >= -1e-8:
                return True
            
            row = -1
            for i in range(m):
                if tableau[i][col] <= 1e-8:
                    continue
                if row == -1 or (
                    tableau[i][n + 1] / tableau[i][col] < tableau[row][n + 1] / tableau[row][col] - 1e-8 or (
                    abs(tableau[i][n + 1] / tableau[i][col] - tableau[row][n + 1] / tableau[row][col]) < 1e-8 and 
                    basic[i] < basic[row])):
                    row = i
            
            if row == -1:
                return False
            pivot(row, col)
    
    row = 0
    for i in range(1, m):
        if tableau[i][n + 1] < tableau[row][n + 1]:
            row = i
    
    if tableau[row][n + 1] <= -1e-8:
        pivot(row, n)
        if not simplex(1) or tableau[m + 1][n + 1] < -1e-8:
            return float('-inf'), []
        
        for i in range(m):
            if basic[i] == -1:
                col = -1
                for j in range(n + 1):
                    if col == -1 or tableau[i][j] < tableau[i][col] - 1e-8 or (
                        abs(tableau[i][j] - tableau[i][col]) < 1e-8 and non_basic[j] < non_basic[col]):
                        col = j
                pivot(i, col)
    
    if not simplex(2):
        return float('inf'), []
    
    solution = [0.0] * n
    for i in range(m):
        if basic[i] < n:
            solution[basic[i]] = tableau[i][n + 1]
    
    return tableau[m][n + 1], solution

def main():
    data = sys.stdin.read().split()
    if not data:
        return
    
    n = int(data[0])
    idx = 1
    coords = []
    for i in range(n):
        x = float(data[idx]); y = float(data[idx + 1]); idx += 2
        coords.append(Point(x, y))
    
    m = n * (n - 1) // 2
    A = [[0.0] * n for _ in range(m)]
    b = [0.0] * m
    c = [1.0] * n
    
    k = 0
    for i in range(n):
        for j in range(i + 1, n):
            A[k][i] = 1.0
            A[k][j] = 1.0
            b[k] = euclidean_dist(coords[i], coords[j])
            k += 1
    
    result, _ = linear_program_solution(A, b, c)
    print(f"{result:.2f}")

if __name__ == "__main__":
    main()