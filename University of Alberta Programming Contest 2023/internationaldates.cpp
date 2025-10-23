#include <bits/stdc++.h>

using namespace std;

int a, b;

int main() {

    scanf("%d/%d/", &a, &b);

    if (a > 12) cout << "EU\n";
    else if (b > 12) cout << "US\n";
    else cout << "either\n";

    return 0;
}