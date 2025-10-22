#include <bits/stdc++.h>
using namespace std;

struct Time {
    int h, m;
    vector<string> path;
};

string format(int h, int m) {
    string s;
    s += char('0' + h/10);
    s += char('0' + h%10);
    s += ':';
    s += char('0' + m/10);
    s += char('0' + m%10);
    return s;
}

int main() {
    string start_str, target_str;
    cin >> start_str >> target_str;
    
    int start_h = stoi(start_str.substr(0, 2));
    int start_m = stoi(start_str.substr(3, 2));
    int target_h = stoi(target_str.substr(0, 2));
    int target_m = stoi(target_str.substr(3, 2));
    
    vector<vector<bool>> visited(24, vector<bool>(60, false));
    queue<Time> q;
    
    vector<string> initial_path = {format(start_h, start_m)};
    q.push({start_h, start_m, initial_path});
    visited[start_h][start_m] = true;
    
    while (!q.empty()) {
        Time current = q.front(); q.pop();
        
        if (current.h == target_h && current.m == target_m) {
            cout << current.path.size() << "\n";
            for (const string& s : current.path) {
                cout << s << "\n";
            }
            return 0;
        }
        
        // Try all digit changes
        int digits[4] = {current.h / 10, current.h % 10, current.m / 10, current.m % 10};
        
        for (int i = 0; i < 4; i++) {
            // Increase digit
            int new_digits[4] = {digits[0], digits[1], digits[2], digits[3]};
            new_digits[i] = (new_digits[i] + 1) % 10;
            
            int new_h = new_digits[0] * 10 + new_digits[1];
            int new_m = new_digits[2] * 10 + new_digits[3];
            
            if (new_h >= 0 && new_h <= 23 && new_m >= 0 && new_m <= 59 && !visited[new_h][new_m]) {
                visited[new_h][new_m] = true;
                vector<string> new_path = current.path;
                new_path.push_back(format(new_h, new_m));
                q.push({new_h, new_m, new_path});
            }
            
            // Decrease digit  
            new_digits[0] = digits[0]; new_digits[1] = digits[1];
            new_digits[2] = digits[2]; new_digits[3] = digits[3];
            new_digits[i] = (new_digits[i] - 1 + 10) % 10;
            
            new_h = new_digits[0] * 10 + new_digits[1];
            new_m = new_digits[2] * 10 + new_digits[3];
            
            if (new_h >= 0 && new_h <= 23 && new_m >= 0 && new_m <= 59 && !visited[new_h][new_m]) {
                visited[new_h][new_m] = true;
                vector<string> new_path = current.path;
                new_path.push_back(format(new_h, new_m));
                q.push({new_h, new_m, new_path});
            }
        }
    }
    
    return 0;
}