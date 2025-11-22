#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        int next;
        cin >> next;
        
        if (next & 1 == 1) {
            cout << next << " is odd" << endl;
        } else {
            cout << next << " is even" << endl;
        }
    }
    
    return 0;
}