def valid_vert(r1, c1, r2, c2, n, m, grid):
    for i in range(n):
        for j in range(m):
            i1 = i
            j1 = 2 * c1 - j + 1
            if i1 < 0 or i1 >= n or j1 < 0 or j1 >= m:
                if grid[i][j] == '.':
                    return False
                else:
                    continue
            if grid[i][j] == grid[i1][j1]:
                return False
    return True

def get_vert(n, m, grid, rv):
    for i in range(m):
        r1, c1, r2, c2 = 0, i, n - 1, i
        if valid_vert(r1, c1, r2, c2, n, m, grid):
            rv.add((r1, c1, r2, c2))
            return

def valid_hor(r1, c1, r2, c2, n, m, grid):
    for i in range(n):
        for j in range(m):
            i1 = 2 * r1 - i + 1
            j1 = j
            if i1 < 0 or i1 >= n or j1 < 0 or j1 >= m:
                if grid[i][j] == '.':
                    return False
                else:
                    continue
            if grid[i][j] == grid[i1][j1]:
                return False
    return True

def get_hor(n, m, grid, rv):
    for i in range(n):
        r1, c1, r2, c2 = i, 0, i, m - 1
        if valid_hor(r1, c1, r2, c2, n, m, grid):
            rv.add((r1, c1, r2, c2))
            return

def valid_diag1(r1, c1, r2, c2, n, m, grid):
    s = r1 + c1
    for i in range(n):
        for j in range(m):
            i1 = s - j
            j1 = s - i
            if i1 < 0 or i1 >= n or j1 < 0 or j1 >= m:
                if grid[i][j] == '.':
                    return False
                else:
                    continue
            if i == i1 and j == j1:
                if grid[i][j] == '.':
                    return False
                else:
                    continue
            if grid[i][j] == grid[i1][j1]:
                return False
    return True

def get_diag1(n, m, grid, rv):
    for i in range(n):
        for j in range(m):
            if j != 0 and i != n - 1:
                continue
            r1, c1 = i, j
            r2, c2 = i, j
            while r2 >= 0 and c2 < m:
                r2 -= 1
                c2 += 1
            r2 += 1
            c2 -= 1
            if valid_diag1(r1, c1, r2, c2, n, m, grid):
                rv.add((r1, c1, r2, c2))
                return

def valid_diag2(r1, c1, r2, c2, n, m, grid):
    s = r1 - c1
    for i in range(n):
        for j in range(m):
            i1 = s + j
            j1 = i - s
            if i1 < 0 or i1 >= n or j1 < 0 or j1 >= m:
                if grid[i][j] == '.':
                    return False
                else:
                    continue
            if i == i1 and j == j1:
                if grid[i][j] == '.':
                    return False
                else:
                    continue
            if grid[i][j] == grid[i1][j1]:
                return False
    return True

def get_diag2(n, m, grid, rv):
    for i in range(n):
        for j in range(m):
            if j != 0 and i != 0:
                continue
            r1, c1 = i, j
            r2, c2 = i, j
            while r2 < n and c2 < m:
                r2 += 1
                c2 += 1
            r2 -= 1
            c2 -= 1
            if valid_diag2(r1, c1, r2, c2, n, m, grid):
                rv.add((r1, c1, r2, c2))
                return

def main():
    n, m = map(int, input().split())
    grid = []
    for _ in range(n):
        grid.append(input().strip())
    
    rv = set()
    get_vert(n, m, grid, rv)
    get_hor(n, m, grid, rv)
    get_diag1(n, m, grid, rv)
    get_diag2(n, m, grid, rv)
    
    if rv:
        first = sorted(rv)[0]
        print(f"{first[0] + 1} {first[1] + 1} {first[2] + 1} {first[3] + 1}")

if __name__ == "__main__":
    main()