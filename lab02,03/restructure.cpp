#include <bits/stdc++.h>

using namespace std;


vector<int> par, go;

int get(int x) {
	if (par[x] == x)
		return x;
	return par[x] = get(par[x]);
}

int get_last(int x) {
	if (go[x] == x)
		return x;
	return go[x] = get_last(go[x]);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, q;
	cin >> n >> q;
	par.resize(n);
	go.resize(n);
	for (int i = 0; i < n; ++i) {
		par[i] = i;
		go[i] = i;
	}

	int t, x, y;
	for (int i = 0; i < q; ++i) {
		cin >> t >> x >> y, --x, --y;
		if (t == 1) {
			par[get(x)] = get(y);
		} else if (t == 2) {
			for (int j = x; j <= y;) {
				par[get(x)] = get(j);
				int k = get_last(j) + 1;
				go[get_last(j)] = get_last(y);
				j = k;
			}
		} else {
			cout << (get(x) == get(y) ? "YES\n" : "NO\n");
		}
	}


	return 0;
}
