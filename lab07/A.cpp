#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9;

unsigned int c, d;
unsigned int cur = 0;
unsigned int nextRand() {
	cur = cur * c + d;
	return cur >> 8;
}

vector<unsigned int> a(n + 1);

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int m, q;
	cin >> m >> q >> c >> d;
	for (int i = 0; i < m; ++i) {
		int add = nextRand();
		int l = nextRand();
		int r = nextRand();
		if (l > r) swap(l, r);
		a[l] += add;
		a[r + 1] -= add;
	}

	for (int i = 1; i < n; ++i)
		a[i] += a[i - 1];
	for (int i = 1; i < n; ++i)
		a[i] += a[i - 1];

	unsigned int ans = 0;
	for (int i = 0; i < q; ++i) {
		int l = nextRand();
		int r = nextRand();
		if (l > r) swap(l, r);
		ans += a[r] - (l > 0 ? a[l - 1] : 0);
	}
	cout << ans;

	return 0;
}
