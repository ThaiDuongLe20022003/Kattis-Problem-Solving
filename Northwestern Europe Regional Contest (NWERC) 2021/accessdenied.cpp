#include <bits/stdc++.h>

using namespace std;

int input() {
    string s;
    getline(cin, s);
    if (s == "ACCESS GRANTED")
        exit(0);
    int t = 0;
    for (auto i: s) {
        if (i >= '0' and i <= '9')
            t = t * 10 + i - '0';
    }
    return t;
}

int32_t main() {
    int len = -1;
    for (int i = 1, t; len == -1 and i <= 20; i++) {
        cout << string(i, '0') << endl << flush;
        t = input();
        if (t != 5) len = i;
    }
    vector<char> ans(len), ch;
    for (char i = '0'; i <= '9'; i++) ch.push_back(i);
    for (auto i = 'a'; i <= 'z'; i++) ch.push_back(i);
    for (auto i = 'A'; i <= 'Z'; i++) ch.push_back(i);

    for (int i = 0, t; i < len; i++) {
        for (auto c: ch) {
            for (int j = 0; j < i; j++)
                cout << ans[j];
            for (int j = i; j < len; j++)
                cout << c;
            cout << endl << flush;
            t = input();
            if (t == 5 + (i + 1) * 9) continue;
            ans[i] = c;
            break;
        }
    }
    for( auto i : ans )
        cout << i;
    cout << endl << flush;
    return 0;
}