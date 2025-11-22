#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
using namespace std;

bool isPrime(int n) {
    if (n == 1) return false;
    for (int i = 2; i < (int)(sqrt(n) + 1); i++)
        if (n % i == 0)
            return false;
    return true;
}

int main() {
    vector<int> primes;
    primes.push_back(2);
    
    for (int i = 3; i < 32000; i += 2)
        if (isPrime(i))
            primes.push_back(i);
    
    int cases;
    cin >> cases;
    
    for (int zax = 0; zax < cases; zax++) {
        int count = 0;
        string str = "";
        int num;
        cin >> num;
        
        for (int i = 0; i < primes.size(); i++) {
            int low = primes[i];
            int high = num - primes[i];
            
            if (high < low)
                break;
            
            // Check if high is prime using binary search
            bool found = binary_search(primes.begin(), primes.end(), high);
            
            if (found) {
                count++;
                str += to_string(low) + "+" + to_string(high) + "\n";
            }
        }
        
        cout << num << " has " << count << " representation(s)" << endl;
        cout << str;
    }
    
    return 0;
}