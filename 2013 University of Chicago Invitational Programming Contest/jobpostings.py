import sys
from typing import List, Tuple, TypeVar, Generic

# Set recursion limit higher for safety, though not strictly necessary for this iterative algorithm
# sys.setrecursionlimit(200000)

T = TypeVar('T', int, float)

def jonker_volgenant(C: List[List[T]]) -> Tuple[List[int], T]:
    """
    Jonker-Volgenant algorithm for the minimum cost assignment problem.
    C: cost matrix (n x m)
    Returns: (row_match, cost)
        row_match: list of column indices assigned to each row (size n)
        cost: the minimum total cost
    """
    n = len(C)
    if n == 0:
        return [], 0
    m = len(C[0])
    if m == 0:
        return [-1] * n, 0

    # Initialize
    dist: List[T] = [0] * m
    potential: List[T] = [0] * m
    row_match: List[int] = [-1] * n  # row_match[i] = column assigned to row i
    col_match: List[int] = [-1] * m  # col_match[j] = row assigned to column j
    cols: List[int] = list(range(m))
    prev: List[int] = [0] * m

    for i in range(n):
        # Phase 1: Find an augmenting path
        d: T = 0
        c1: int = -1
        temp: int = 0

        for c in range(m):
            dist[c] = C[i][c] - potential[c]
            prev[c] = i

        s: int = 0
        t: int = 0
        
        while True:
            if s == t:
                temp = s
                d = dist[cols[t]]
                t += 1
                
                # Find minimum dist in cols[t..m-1] and move it to cols[t]
                for j in range(t, m):
                    c1 = cols[j]
                    if d < dist[c1]:
                        continue
                    if d > dist[c1]:
                        d = dist[c1]
                        t = s
                    
                    # C++: cols[j] = exchange(cols[t++], c1);
                    # Python equivalent: swap cols[j] and cols[t], then increment t
                    cols[j], cols[t] = cols[t], c1
                    t += 1

                for j in range(s, t):
                    c1 = cols[j]
                    if col_match[c1] == -1:
                        # Found an unassigned column, break to done
                        break
                else:
                    # No unassigned column found in cols[s..t-1], continue outer loop
                    pass
                
                if col_match[c1] == -1:
                    break # Go to done
            
            c2 = cols[s]
            s += 1
            r = col_match[c2]
            
            for j in range(t, m):
                c1 = cols[j]
                reduced_cost = C[r][c1] - C[r][c2] + potential[c2] - potential[c1] + d
                
                if dist[c1] > reduced_cost:
                    dist[c1] = reduced_cost
                    prev[c1] = r

                    if dist[c1] == d:
                        if col_match[c1] == -1:
                            break # Go to done
                        
                        # C++: cols[j] = exchange(cols[t++], c1);
                        cols[j], cols[t] = cols[t], c1
                        t += 1
            else:
                continue # Continue outer while loop
            
            if col_match[c1] == -1:
                break # Go to done

        # Phase 2: Update potentials and augment path
        
        # Update potentials
        for j in range(temp):
            potential[cols[j]] += dist[cols[j]] - d
        
        # Augment path
        r = -1
        current_c = c1
        while r != i:
            r = col_match[current_c] = prev[current_c]
            # C++: swap(current_c, row_match[r]);
            current_c, row_match[r] = row_match[r], current_c

    # Calculate total cost
    cost: T = 0
    for i in range(n):
        if row_match[i] != -1:
            cost += C[i][row_match[i]]
            
    return row_match, cost

# Main function logic (Problem specific)
def solve():
    # Read all input at once for faster processing in competitive programming
    try:
        data = sys.stdin.read().split()
    except:
        return

    if not data:
        return

    data_iter = iter(data)

    while True:
        try:
            n = int(next(data_iter))
            m = int(next(data_iter))
        except StopIteration:
            break
        except ValueError:
            # Handle case where input might be malformed
            break

        if n == 0 and m == 0:
            break

        positions = []
        for _ in range(n):
            try:
                positions.append(int(next(data_iter)))
            except StopIteration:
                return

        total = sum(positions)

        # cols[job] stores the column indices assigned to job
        cols_map = [[] for _ in range(n)]
        current_col = 0
        for job in range(n):
            for _ in range(positions[job]):
                cols_map[job].append(current_col)
                current_col += 1

        # Cost matrix: n_rows = m, n_cols = total
        n_rows = m
        n_cols = total
        
        # Initialize cost matrix with 0s
        cost: List[List[int]] = [[0] * n_cols for _ in range(n_rows)]

        for i in range(m):
            try:
                y = int(next(data_iter))
                c1 = int(next(data_iter))
                c2 = int(next(data_iter))
                c3 = int(next(data_iter))
                c4 = int(next(data_iter))
            except StopIteration:
                return

            c = 4 * y
            jobs = [c1, c2, c3, c4]
            
            for job in jobs:
                # Assuming job indices are 0-based (0 to n-1)
                if 0 <= job < n:
                    for col_idx in cols_map[job]:
                        if 0 <= i < n_rows and 0 <= col_idx < n_cols:
                            cost[i][col_idx] = -c
                c -= 1
        
        # The Jonker-Volgenant algorithm finds the minimum cost.
        # The problem seems to be a maximum cost problem, as the cost is negated.
        # The C++ code calls: -jonker_volgenant(cost).second
        
        try:
            _, min_cost = jonker_volgenant(cost)
            print(f"{-min_cost}")
        except Exception as e:
            # In case of an error in the JV algorithm (e.g., non-square matrix handling)
            # print an error or a default value.
            # For this problem, the matrix is m x total, which is non-square if m != total.
            # The JV implementation handles non-square matrices.
            print(f"Error during assignment: {e}", file=sys.stderr)
            pass

if __name__ == "__main__":
    solve()