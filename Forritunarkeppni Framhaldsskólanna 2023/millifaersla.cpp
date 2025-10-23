#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    
    int min_fee = min({a, b, c});
    
    if (min_fee == a) {
        cout << "Monnei" << endl;
    } else if (min_fee == b) {
        cout << "Fjee" << endl;
    } else {
        cout << "Dolladollabilljoll" << endl;
    }
    
    return 0;
}