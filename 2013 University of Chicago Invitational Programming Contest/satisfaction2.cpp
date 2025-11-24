#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef vector<unsigned> bs;

int N, M;
string VARS;
vector<bs> pure_var;
vector<string> P;
int ch_map[256];

bs bs_ones() {
  return bs(M, 0xFFFFFFFFU);
}

bs bs_zeros() {
  return bs(M, 0);
}

bool bs_get(const bs& x, unsigned i) {
  return x[i >> 5] & 1U << (i & 0x1F);
}

void bs_set(bs& x, unsigned i) {
  x[i >> 5] |= 1U << (i & 0x1F);
}

bs bs_not(const bs& x) {
  bs r(M, 0);
  for(int i = 0; i < M; i++) {
    r[i] = ~x[i];
  }
  return r;
}

bs bs_and(const bs& x, const bs& y) {
  bs r(M, 0);
  for(int i = 0; i < M; i++) {
    r[i] = x[i] & y[i];
  }
  return r;
}

bs bs_or(const bs& x, const bs& y) {
  bs r(M, 0);
  for(int i = 0; i < M; i++) {
    r[i] = x[i] | y[i];
  }
  return r;
}

bs parse(const string& S, int s, int e) {
  vector<bs> sts;

  int j = s;
  int dep = 0;
  bool last_and = false;
  for(int i = s; i <= e; i++) {
    if(i < e && (S[i] == '(' || S[i] == ')')) {
      dep += S[i] == '(' ? 1 : -1;
    }
    if(dep > 0) continue;
    if(i == e && sts.empty()) {
      if(S[s] == '~') {
        return bs_not(parse(S, s + 1, e));
      } else if(S[s] == '(') {
        assert(S[e - 1] == ')');
        return parse(S, s + 1, e - 1);
      } else {
        assert(isupper(S[s]) && e - s == 1);
        return pure_var[ch_map[S[s]]];
      }
    } else if(i == e || S[i] == '&' || S[i] == '|') {
      bs val = parse(S, j, i);
      if(last_and) {
        sts.back() = bs_and(sts.back(), val);
      } else {
        sts.push_back(val);
      }
      last_and = S[i] == '&';
      j = i + 1;
    }
  }

  bs res = sts[0];
  for(int i = 1; i < sts.size(); i++) {
    res = bs_or(res, sts[i]);
  }
  return res;
}

void solve(const bs& base, int s, int e) {
  for(int i = s; i < e; i++) {
    if(P[i] == "checkpoint") {
      unsigned msk_a = 0;
      unsigned msk_b = 0;
      for(unsigned i = 0; i < 1 << N; i++) {
        if(bs_get(base, i)) {
          msk_a |= i;
          msk_b |= ~i;
        }
      }
      msk_b &= (1U << N) - 1;
      cout << ">";
      if(msk_a || msk_b) {
        for(int i = 0; i < N; i++) {
          if(~(msk_a & msk_b) & 1U << i) {
            cout << (char)(msk_a & 1U << i ? VARS[i] : tolower(VARS[i]));
          }
        }
      } else {
        cout << "unreachable";
      }
      cout << '\n';
    } else if(P[i] == "if") {
      assert(i + 2 < e && P[i + 2] == "then");
      bs cond = parse(P[i + 1], 0, P[i + 1].size());
      i += 3;

      int dep = 1;
      int j;
      for(j = i; dep > 0; j++) {
        assert(j < e);
        if(P[j] == "if") {
          dep++;
        } else if(P[j] == "fi") {
          dep--;
        } else if(P[j] == "else" && dep == 1) {
          solve(bs_and(base, cond), i, j);
          cond = bs_not(cond);
          i = j + 1;
        }
      }
      solve(bs_and(base, cond), i, j - 1);
      i = j - 1;
    } else {
      assert(0 && "parse fail");
    }
  }
}

int main() {
  string S;
  for(int ch = cin.get(); ch != -1; ch = cin.get()) {
    if(isspace(ch)) {
      if(!S.empty()) P.push_back(S);
      S.clear();
      continue;
    }
    if(isupper(ch)) {
      VARS += (char)ch;
    }
    if(!S.empty() && islower(S[0]) != islower(ch)) {
      if(!S.empty()) P.push_back(S);
      S.clear();
    }
    S += (char)ch;
  }
  if(!S.empty()) P.push_back(S);

  sort(VARS.begin(), VARS.end());
  VARS.resize(unique(VARS.begin(), VARS.end()) - VARS.begin());
  for(int i = 0; i < VARS.size(); i++) {
    ch_map[VARS[i]] = i;
  }

  while(VARS.size() < 5) VARS += '?';
  N = VARS.size();
  M = 1 << (N - 5);

  bs base = bs_ones();
  for(int i = 0; i < N; i++) {
    pure_var.push_back(bs_zeros());
  }
  for(int i = 0; i < 1 << N; i++) {
    for(int j = 0; j < N; j++) {
      if(i & 1 << j) {
        bs_set(pure_var[j], i);
      }
    }
  }
  solve(base, 0, P.size());
  return 0;
}