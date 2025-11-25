import sys
import math

def solve():
    # Fast input reading for competitive programming
    try:
        # Read N
        n_line = sys.stdin.readline()
        if not n_line:
            return
        n = int(n_line.strip())
    except EOFError:
        return
    except ValueError:
        return

    try:
        # Read the permutation
        p_line = sys.stdin.readline()
        if not p_line:
            return
        p = list(map(int, p_line.split()))
    except EOFError:
        return
    except ValueError:
        return

    # pos[c] stores the index of card 'c' in the shuffled deck.
    # Card values are 1 to n, so we use a list of size n+1.
    # Python lists are 0-indexed, so pos[1] will store the index of card 1, etc.
    pos = [0] * (n + 1)
    for i in range(n):
        card = p[i]
        pos[card] = i

    # Core logic: count the number of blocks
    num_blocks = 0
    last_pos = -1 # Position of the last card (card - 1) placed in the current block

    # Iterate through the cards in their original sorted order (1, 2, ..., n)
    for card in range(1, n + 1):
        current_pos = pos[card]
        
        # If the current card's position is less than the last card's position,
        # it means this card must start a new block.
        if current_pos < last_pos:
            num_blocks += 1
        last_pos = current_pos

    # The loop counts the number of times a new block *starts*.
    # The first block is not counted in the loop, so we add 1.
    num_blocks += 1

    # The minimum number of shuffles 'k' is the smallest integer such that 2^k >= num_blocks.
    # This is equivalent to ceil(log2(num_blocks)).
    
    # We can use the bit_length method for an efficient log2 calculation.
    # num_blocks - 1 because bit_length gives the number of bits required to represent the number,
    # which is equivalent to floor(log2(num_blocks)) + 1.
    # For example, bit_length(1) = 1, bit_length(2) = 2, bit_length(3) = 2, bit_length(4) = 3.
    # We want:
    # B=1 -> k=0
    # B=2 -> k=1
    # B=3 -> k=2
    # B=4 -> k=2
    # B=5 -> k=3
    # The correct way is to find the smallest power of 2 >= num_blocks.
    
    # A simpler way is to use the while loop, which is clear and efficient enough
    # since num_blocks is at most 1,000,001.
    result = 0
    power_of_2 = 1
    while power_of_2 < num_blocks:
        power_of_2 *= 2
        result += 1

    print(result)

if __name__ == "__main__":
    solve()