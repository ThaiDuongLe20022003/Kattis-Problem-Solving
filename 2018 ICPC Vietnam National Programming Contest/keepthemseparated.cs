using System;

class Program {
    const int MAX_N = 2503;
    const int MOD = 1000000782;
    const int MAX_Q = 100005;
    const int BASE = 102240;

    struct Element {
        public int x1, y1, x2, y2;
    }

    static int[,] fw = new int[MAX_N, MAX_N];
    static int[] power = new int[MAX_Q];
    static Element[] a = new Element[MAX_Q];

    static void Add(ref int a, int b) {
        a = (a + b) % MOD;
    }

    static void UpdateSingle(int x, int y, int val) {
        for (int i = x; i < MAX_N; i += i & -i) {
            for (int j = y; j < MAX_N; j += j & -j) {
                Add(ref fw[i, j], val);
            }
        }
    }

    static void UpdateRange(int x1, int y1, int x2, int y2, int val) {
        UpdateSingle(x1, y1, val);
        UpdateSingle(x1, y2 + 1, MOD - val);
        UpdateSingle(x2 + 1, y1, MOD - val);
        UpdateSingle(x2 + 1, y2 + 1, val);
    }

    static int Get(int x, int y) {
        int sum = 0;
        for (int i = x; i > 0; i -= i & -i) {
            for (int j = y; j > 0; j -= j & -j) {
                Add(ref sum, fw[i, j]);
            }
        }
        return sum;
    }

    static void Main() {
        power[0] = 1;
        
        int query = int.Parse(Console.ReadLine());
        for (int i = 1; i <= query; i++) {
            power[i] = (int)((long)power[i - 1] * BASE % MOD);
        }
        
        for (int i = 1; i <= query; i++) {
            string[] input = Console.ReadLine().Split();
            int type = int.Parse(input[0]);
            
            if (type == 1) {
                a[i].x1 = (int.Parse(input[1]) + 1) / 2;
                a[i].y1 = (int.Parse(input[2]) + 1) / 2;
                a[i].x2 = (int.Parse(input[3]) - 1) / 2;
                a[i].y2 = (int.Parse(input[4]) - 1) / 2;
                int x = power[i];
                UpdateRange(a[i].x1, a[i].y1, a[i].x2, a[i].y2, x);
            }
            else if (type == 2) {
                int p = int.Parse(input[1]);
                int x = MOD - power[p];
                UpdateRange(a[p].x1, a[p].y1, a[p].x2, a[p].y2, x);
            }
            else {
                int x1 = int.Parse(input[1]) / 2;
                int y1 = int.Parse(input[2]) / 2;
                int x2 = int.Parse(input[3]) / 2;
                int y2 = int.Parse(input[4]) / 2;
                int K2 = Get(x2, y2);
                int K1 = Get(x1, y1);
                Console.Write(K1 == K2 ? 'Y' : 'N');
            }
        }
    }
}