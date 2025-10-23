#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string a, b;
    cin >> a >> b;
    
    string result;
    result.reserve(a.size() + b.size()); // Pre-allocate memory
    
    // Merge the two sorted strings
    int i = 0, j = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] <= b[j]) {
            result += a[i++];
        } else {
            result += b[j++];
        }
    }
    
    // Append remaining characters
    while (i < a.size()) result += a[i++];
    while (j < b.size()) result += b[j++];
    
    cout << result << "\n";
    
    return 0;
}