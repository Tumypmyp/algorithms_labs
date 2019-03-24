#include <bits/stdc++.h>

using namespace std;

vector<int> par;

int get(int x) {
	if (par[x] == x)
		return x;
	return par[x] = get(par[x]);
}

mt19937 gen(123);

int rnd(int L, int R) {
	return (abs((int)gen())) % (R - L) + L;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	par.resize(n);
	for (int i = 0; i < n; ++i)
		par[i] = i;

	for (int i = 0; i < m; ++i) {
		if (rnd(0, 3) > 0) {
			int x = rnd(0, n), y = get(rnd(0, n));
			while (get(x) == y) {
				x = rnd(0, n);
			}
			par[get(x)] = get(y);
			cout << "0 " << x + 1 << " " << y + 1 << "\n";
		} else {
			cout << "1 " << rnd(0, n) + 1 << " " << rnd(0, n) + 1 << "\n";
		}
	}

	return 0;
}
