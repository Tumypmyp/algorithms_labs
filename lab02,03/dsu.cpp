#include <bits/stdc++.h>

using namespace std;

struct Node{
	int v, min_v, max_v, sz, par;
};

vector<Node> a;

int get(int x) {
	if (a[x].par == x)
		return x;
	return a[x].par = get(a[x].par);
}

void merge(int x, int y) {
	x = get(x);
	y = get(y);
	if (a[x].sz > a[y].sz)
		swap(x, y);
	if (x == y)
		return;
	// cout << x << " " << y << "\n";
	a[x].par = y;
	a[y].max_v = max(a[y].max_v, a[x].max_v);
	a[y].min_v = min(a[y].min_v, a[x].min_v);
	a[y].sz += a[x].sz;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	a.resize(n + 1);
	for (int i = 1; i <= n; ++i)
		a[i] = {i, i, i, 1, i};

	string s;
	int x, y;
	while (cin >> s) {
		if (s[0] == 'u') {
			cin >> x >> y;
			merge(x, y);
		} else {
			cin >> x;
			int ind = get(x);
			cout << a[ind].min_v << " " << a[ind].max_v << " " << a[ind].sz << "\n";
			}
		// for (auto &p : a)
		// 	cout << p.v << " " << p.min_v << " " << p.max_v << " " << p.sz << " " << p.par << ", ";
		// cout << "\n";
	}

	return 0;
}
