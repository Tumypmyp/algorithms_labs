#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9;

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<int> lg(n + 1);
	for (int i = 2; i <= n; ++i)
		lg[i] = lg[i / 2] + 1;

	vector<vector<int>> a(n, vector<int> (lg[n] + 1));
	cin >> a[0][0];

	for (int i = 1; i < n; ++i)
		a[i][0] = (23 * a[i - 1][0] + 21563) % 16714589;

	for (int d = 0; d < (int)a[0].size() - 1; ++d) {
		for (int i = 0; i < n; ++i)
			if (i + (1 << d) < n)
				a[i][d + 1] = min(a[i][d], a[i + (1 << d)][d]);
	}
	/*/
	for (int d = 0; d < (int)a[0].size(); ++d) {
		for (int i = 0; i < n; ++i)
			cout << a[i][d] << "\t";
		cout << "\n";
	}
	cout << "ok" << endl;
	//*/
	int l, r;
	cin >> l >> r;
	int u = min(l, r) - 1, v = (max(l, r));
	int d = v - u;
	// cout << u << " " << v << endl;
	int ans = min(a[u][lg[d]], a[v - (1 << lg[d])][lg[d]]);
	// cout << ans << endl;

	for (int i = 1; i < m; ++i) {
		l = (17 * l + 751 + ans + 2 * i) % n + 1;
		r = (13 * r + 593 + ans + 5 * i) % n + 1;
		int u = min(l, r) - 1, v = (max(l, r));
		d = v - u;
		// cout << u << " " << v << endl;
		// cout << u << " - " << u + (1 << lg[d]) << ", " << v - (1 << lg[d]) << " - " << v << endl;
		ans = min(a[u][lg[d]], a[v - (1 << lg[d])][lg[d]]);
		// cout << ans << " ans\n" << endl;
	}

	cout << l << " " << r << " " << ans;
	return 0;
}
