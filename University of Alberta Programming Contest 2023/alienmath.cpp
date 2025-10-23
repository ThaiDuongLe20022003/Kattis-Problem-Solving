#include <bits/stdc++.h>

using namespace std;

int main() {
  int b;
  cin >> b;

  unordered_map<string, int> digits;

  for (int i = 0; i < b; ++i) {
    string dig;
    cin >> dig;
    digits[dig] = i;
  }

  string number;
  cin >> number;

  string dig = "";
  int val = 0;

  for (char c : number) {
    dig += c;
    if (digits.find(dig) != digits.end()) {
      val = val*b + digits[dig];
      dig = "";
    }
  }

  cout << val << endl;

  return 0;
}