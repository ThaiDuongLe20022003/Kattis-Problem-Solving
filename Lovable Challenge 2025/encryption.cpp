#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s, d, l;
    cin >> s >> d >> l;

    string result = "";
    int ptr_s = 0, ptr_d = 0, ptr_l = 0;

    // Loop through the LCS string
    while (ptr_l < l.length()) {
        char l_char = l[ptr_l];

        // 1. Add all characters from s until we find the LCS char
        while (ptr_s < s.length() && s[ptr_s] != l_char) {
            result += s[ptr_s];
            ptr_s++;
        }

        // 2. Add all characters from d until we find the LCS char
        while (ptr_d < d.length() && d[ptr_d] != l_char) {
            result += d[ptr_d];
            ptr_d++;
        }

        // 3. Add the common LCS char
        result += l_char;

        // 4. Advance all pointers
        ptr_s++;
        ptr_d++;
        ptr_l++;
    }

    // 5. Add any remaining characters from s and d
    if (ptr_s < s.length()) {
        result += s.substr(ptr_s);
    }
    if (ptr_d < d.length()) {
        result += d.substr(ptr_d);
    }

    cout << result << endl;

    return 0;
}