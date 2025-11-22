#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

class Binomial {
private:
    static std::vector<std::vector<int>> mem;
public:
    static int coefficient(int n, int k) {
        if (mem.size() <= n) {
            for (int i = mem.size(); i <= n; i++) {
                std::vector<int> row(i + 1, 1);
                for (int j = 1; j < i; j++) {
                    row[j] = mem[i-1][j-1] + mem[i-1][j];
                }
                mem.push_back(row);
            }
        }
        return mem[n][k];
    }
};

std::vector<std::vector<int>> Binomial::mem = {{1}};

class Polynomial {
private:
    std::vector<double> a;
    std::vector<double> points;
    
public:
    Polynomial(const std::vector<double>& coefficients, int n) : a(coefficients) {
        points.resize(n + 1);
        for (int x = 0; x <= n; x++) {
            points[x] = eval_at(x);
        }
    }
    
    double eval_at(int x) const {
        if (x == 0) return a[0];
        double result = 0.0;
        double power = 1.0;
        for (double coeff : a) {
            result += coeff * power;
            power *= x;
        }
        return result;
    }
    
    double operator[](int x) const {
        return points[x];
    }
};

std::vector<double> find_c(int n, const std::vector<double>& a) {
    Polynomial p(a, n);
    std::vector<double> c;
    c.push_back(p[0]);
    
    for (int i = 0; i < n; i++) {
        double sum = p[i + 1] - p[i];
        for (int j = 0; j < i; j++) {
            sum -= Binomial::coefficient(i, j) * c[j + 1];
        }
        c.push_back(sum);
    }
    return c;
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<double> a(n + 1);
    for (int i = 0; i <= n; i++) {
        std::cin >> a[i];
    }
    
    std::reverse(a.begin(), a.end());
    std::vector<double> c = find_c(n, a);
    
    for (double val : c) {
        std::cout << static_cast<int>(val) << " ";
    }
    std::cout << std::endl;
    
    return 0;
}