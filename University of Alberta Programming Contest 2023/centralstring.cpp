// intentionally not adding any optimizations apart from what is required
// to ensure the running time is O(N*L + N*D*(D+1)^D)

#include <bits/stdc++.h>

using namespace std;

#define MAXN 50

int N, L, D;

// dict = input words, s = candidate central string
string dict[MAXN], s;

// differ[i] is the set of indices where dict[i] and s differ
unordered_set<int> differ[MAXN];

// go through each dict[i] string and add or remove index j if required
void update(int j) {
  for (int i = 0; i < N; ++i)
    if (s[j] != dict[i][j]) differ[i].insert(j);
    else differ[i].erase(j);
}

void solve(int rem) {
  // find a violating string or print s and quit if s is already a valid solution
  int i = 0;
  while (i < N && differ[i].size() <= D) ++i;
  if (i == N) {
    cout << s << endl;
    exit(0);
  }

  if (rem == 0) return;

  // get any D+1 vertices where they differ
  vector<int> different;
  for (int j : differ[i]) {
    different.push_back(j);
    if (different.size() == D+1) break;
  }

  // in turn, try to change s[j] to dict[i][j] for each of these D+1 indices
  for (int j : different) {
    char old = s[j];
    s[j] = dict[i][j];
    update(j);

    solve(rem-1);

    s[j] = old;
    update(j);
  }
}

int main() {
  cin >> N >> L >> D;
  for (int i = 0; i < N; ++i) cin >> dict[i];
  s = dict[0];
  for (int j = 0; j < L; ++j) update(j);
  solve(D);

  cout << 0 << endl;

  return 0;
}