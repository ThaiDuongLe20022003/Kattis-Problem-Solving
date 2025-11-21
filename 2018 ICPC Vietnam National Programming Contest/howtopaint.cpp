#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>
#include <cstring>
#define mod 100003
#define maxn 1005
using namespace std;

long long numerator = 1, denominator = 1, base = 0;
int m, n;
vector<int> a, b;
bool filled[maxn][maxn];
int ups[maxn][maxn], rights[maxn][maxn];

// We only calculate the denominator here
void update_hook(const vector<int>& w) {
	assert(w[0] > 0);
	for (int i = 1; i < w.size(); i++) {
		assert(w[i] <= w[i - 1]);
	}
	memset(filled, false, sizeof filled);
	for (int i = 0; i < w.size(); i++) {
		for (int j = 0; j < w[i]; j++) {
			filled[i][j] = true;
		}
	}
	memset(ups, 0, sizeof ups);
	memset(rights, 0, sizeof rights);

	for (int i = m - 1; i >= 0; i--) {
		for (int j = n - 1; j >= 0; j--) {
			if (filled[i][j]) {
				ups[i][j] = (filled[i + 1][j]) ? (1 + ups[i + 1][j]) : 1;
				rights[i][j] = (filled[i][j + 1]) ? (1 + rights[i][j + 1]) : 1;
				int hook = ups[i][j] + rights[i][j] - 1;
				denominator *= hook;
				denominator %= mod;
			}
		}
	}
}

void multiply(int x) {
	while (x % mod == 0) {
		base++;
		x /= mod;
	}
	numerator *= x;
	numerator %= mod;
}

int main() {
	scanf("%d %d", &m, &n);
	assert(0 < m && m <= 1000);
	assert(0 < n && n <= 1000);

	a.resize(m);
	b.resize(m);
	int p = 0, q = 0;
	for (int i = 0; i < m; i++) {
		scanf("%d", &a[i]);
		assert(a[i] <= n);
		b[i] = n - a[i];
		p += a[i];
		q += b[i];
	}
	sort(b.rbegin(), b.rend());
	update_hook(a);
	update_hook(b);

	// Calculate the numerator
	for (int i = 1; i <= p + q - 2; i++) {
		multiply(i);
	}
	multiply(p);
	multiply(q);

	// numerator * denominator^(mod - 2) is the answer for the second value
	for (int i = 0; i < mod - 2; i++) {
		numerator *= denominator;
		numerator %= mod;
	}

	printf("%lld %lld\n", base, numerator);
	return 0;
}