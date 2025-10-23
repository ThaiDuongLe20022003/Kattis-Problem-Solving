#include <bits/stdc++.h>

const int N = 1e4 + 7;

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int y;
    cin >> y;
    
    vector<int> facts(10, 1);
    
    for (int i = 1; i < 10; ++i)
        facts[i] = facts[i - 1] * i;
    
    string res;
    
    while(y)
    {
        int d = 9;
        while (facts[d] > y)
            --d;
            
        if (d == 1) d = 0;
        res += ('0' + d);   
        
        y -= facts[d];
    }
    
    reverse(res.begin(), res.end());
    
    if (res[0] == '0' and res.size() > 1) res[0] = '1';
    
    cout << res << "\n";
}