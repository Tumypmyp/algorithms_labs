#include <bits/stdc++.h>

using namespace std;

struct Node{
	int v, sz, par;
};

vector<Node> a;

int get_col(int x) {
	if (a[x].par == x)
		return a[x].v;
	return a[x].v ^ get_col(a[x].par);
}

int get(int x) {
	if (a[x].par == x)
		return x;
	return get(a[x].par);
}

void merge(int x, int y) {
	int eq = (get_col(x) == get_col(y));
	x = get(x);
	y = get(y);
	if (a[x].sz > a[y].sz)
		swap(x, y);
	a[x].par = y;
	a[y].sz += a[x].sz;
	a[x].v ^= eq;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	a.resize(n);
	for (int i = 0; i < n; ++i)
		a[i] = {0, 1, i};

	int t, shift = 0, x, y;
	for (int i = 0; i < m; ++i) {
		cin >> t >> x >> y, --x, --y;
		x = (shift + x) % n;
		y = (shift + y) % n;
		if (t == 0) {
			merge(x, y);
		} else {
			if (get_col(x) == get_col(y)) {
				cout << "YES\n";
				shift = (shift + 1) % n;
			} else {
				cout << "NO\n";
			}
		}
		/*/
		for (int i = 0; i < n; ++i) {
			auto p = a[i];
			cout << get_col(i) << " " << p.v << " " << p.sz << " " << p.par << "\n";
		}
		cout << "\n";
		//*/
	}

	return 0;
}
