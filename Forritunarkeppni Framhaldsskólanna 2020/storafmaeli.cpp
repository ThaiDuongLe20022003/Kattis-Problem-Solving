#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    if (n % 10 == 0) {
        cout << "Jebb" << endl;
    } else {
        cout << "Neibb" << endl;
    }
    
    return 0;
}