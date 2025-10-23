#include <map>
#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    map<int, long long> segs;
    segs[2111111111] = 0;
    long long highest = 0;
    for (int i = 0; i < n; i++) {
        int x, sz;
        cin >> x >> sz;
        int x2 = x+sz-1;
        auto it = segs.lower_bound(x);
        long long left_height = it->second, place_at = it->second;
        while (it->first < x2) {
            it = segs.erase(it); // erase covered squares
            place_at = max(place_at, it->second);
        }
        segs[x2] = place_at + sz; // add new square
        if (segs.find(x-1) == segs.end())
            segs[x-1] = left_height; // patch left endpoint if we are splitting a region
        highest = max(highest, place_at + sz);
        cout << highest << endl;
    }
}