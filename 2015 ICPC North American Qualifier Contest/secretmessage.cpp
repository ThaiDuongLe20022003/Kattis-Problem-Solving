#include <iostream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

int main() {
    int testcases;
    cin >> testcases;
    cin.ignore(); // consume newline
    
    for (int zaxbys = 0; zaxbys < testcases; zaxbys++) {
        string str;
        getline(cin, str);
        
        int i = 1;
        int length = str.length();
        
        while (i * i < length)
            i++;
        
        // Pad string with asterisks
        int padded_length = i * i;
        string padded_str = str;
        for (int x = length; x < padded_length; x++)
            padded_str += '*';
        
        // Create 2D vector
        vector<vector<char>> nums(i, vector<char>(i));
        
        // Fill 2D vector
        for (int r = 0; r < i; r++)
            for (int c = 0; c < i; c++)
                nums[r][c] = padded_str[i * r + c];
        
        // Output result
        for (int c = 0; c < i; c++)
            for (int r = i - 1; r >= 0; r--)
                if (nums[r][c] != '*')
                    cout << nums[r][c];
        
        cout << endl;
    }
    
    return 0;
}