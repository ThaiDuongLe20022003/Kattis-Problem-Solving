using System;

class Program {
    const int MAX = 1000100;
    const int SQRT = 1515;
    const int LENGTH = 20;

    static int[] result = new int[MAX];
    static int[,] pw = new int[MAX, LENGTH + 3];

    static int Gcd(int a, int b) {
        while (true) {
            if (a == 0) return b;
            if (b == 0) return a;
            if (a > b) a %= b;
            else b %= a;
        }
    }

    static int GetSum(int p, int q, int k) {
        long res = 0;
        for (int i = 0; i <= k; i++) {
            res += (long)pw[p, i] * pw[q, k - i];
            if (res >= MAX) return MAX;
        }
        return (int)res;
    }

    static void Prepare() {
        for (int i = 1; i < MAX; i++) {
            pw[i, 0] = 1;
            for (int j = 1; j <= LENGTH; j++) {
                long val = (long)pw[i, j - 1] * i;
                pw[i, j] = val < MAX ? (int)val : MAX;
            }
        }

        int numPair = 0;
        for (int k = 2; k <= LENGTH; k++) {
            for (int q = 1; q <= SQRT; q++) {
                if (pw[q, k] >= MAX) break;
                for (int p = q + 1; p <= SQRT; p++) {
                    int sum = GetSum(p, q, k);
                    if (sum >= MAX) break;
                    if (Gcd(p, q) > 1) continue;
                    numPair++;
                    result[sum]++;
                }
            }
        }

        int cnt = 0;
        for (int i = 1; i < MAX; i++) {
            if (result[i] > 0) cnt++;
        }
        Console.Error.WriteLine(cnt);
        Console.Error.WriteLine(numPair);

        for (int i = MAX - 1; i >= 1; i--) {
            for (int j = 2 * i; j < MAX; j += i) {
                result[j] += result[i];
            }
        }
    }

    static int Solve(int n) {
        if (n < 3) return 1;
        int numOne = 1;
        int numTwo = n % 2 == 0 ? n / 2 - 1 : n / 2;
        return numOne + numTwo + result[n];
    }

    static void Main() {
        Prepare();
        int input = int.Parse(Console.ReadLine());
        string[] inputs = Console.ReadLine().Split();
        foreach (string s in inputs) {
            int num = int.Parse(s);
            Console.Write(Solve(num) + " ");
        }
        Console.WriteLine();
    }
}