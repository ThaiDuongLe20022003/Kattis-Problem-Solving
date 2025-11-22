def main():
    n = int(input().strip())
    first_case = True
    
    for _ in range(n):
        if not first_case:
            print()
        first_case = False
        
        x = int(input().strip())
        
        left_weights = []
        right_weights = []
        current_power_of_3 = 1
        
        while x > 0:
            rem = x % 3
            if rem == 1:
                right_weights.append(current_power_of_3)
                x -= 1
            elif rem == 2:
                left_weights.append(current_power_of_3)
                x += 1
            
            x //= 3
            if x > 0:
                if current_power_of_3 > (2**63 - 1) // 3:
                    break
                current_power_of_3 *= 3
        
        # Sort in descending order
        left_weights.sort(reverse=True)
        right_weights.sort(reverse=True)
        
        # Print results
        print("left pan:", end="")
        for weight in left_weights:
            print(f" {weight}", end="")
        print()
        
        print("right pan:", end="")
        for weight in right_weights:
            print(f" {weight}", end="")
        print()

if __name__ == "__main__":
    main()