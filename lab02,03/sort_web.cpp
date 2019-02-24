#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define point pair<int, int>
#define x first
#define y second


int n, m, k;
vector<vector<point>> a;

bool ok(int mask) {
	vector<int> d(n);
	for (int i = 0; i < n; ++i)
		d[i] = (int)((mask >> i) & 1);
	for (auto &v : a)
		for (auto &p : v)
			if (d[p.x] > d[p.y])
				swap(d[p.x], d[p.y]);
	for (int i = 0; i < n - 1; ++i)
		if (d[i] > d[i + 1])
			return false;
	return true;
}




int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> m >> k;
	a.resize(n, vector<point> (k));

	int r;
	for (int i = 0; i < k; ++i) {
		cin >> r;
		a[i].resize(r);
		for (auto &p : a[i])
			cin >> p.x >> p.y, --p.x, --p.y;
	}
	for (int mask = 0; mask < (1 << n); ++mask) {
		if (!ok(mask)) {
			cout << "No";
			return 0;
		}
	}
	cout << "Yes";



	return 0;
}
