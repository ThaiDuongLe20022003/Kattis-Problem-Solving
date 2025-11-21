def main():
    ntests = int(input())
    fi = "Chikapu"
    se = "Bash"
    
    for _ in range(ntests):
        s = input().strip()
        n = len(s)
        
        if s[0] != s[-1]:
            print(se if n % 2 == 0 else fi)
        else:
            print(se if n % 2 == 1 else fi)

if __name__ == "__main__":
    main()