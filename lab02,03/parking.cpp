#include <bits/stdc++.h>

using namespace std;


vector<int> par;

int get(int x) {
	if (par[x] == x)
		return x;
	return par[x] = get(par[x]);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	par.resize(n);
	for (int i = 0; i < n; ++i)
		par[i] = i;

	int pl;
	for (int i = 0; i < n; ++i) {
		cin >> pl, pl--;
		cout << get(pl) + 1 << " ";
		par[get(pl)] = (get(pl) + 1) % n;
	}


	return 0;
}
