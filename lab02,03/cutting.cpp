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
	int n, m, k;
	cin >> n >> m >> k;
	par.resize(n);
	for (int i = 0; i < n; ++i) {
		par[i] = i;
	}
	int x, y;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y;
	}
	string s;
	vector<pair<char, pair<int, int>>> q;
	for (int i = 0; i < k; ++i) {
		cin >> s >> x >> y, --x, --y;
		q.push_back({s[0], {x, y}});
	}
	reverse(q.begin(), q.end());
	vector<string> ans;
	for (auto &p : q) {
		if (p.first == 'a') {
			ans.push_back((get(p.second.first) == get(p.second.second) ? "YES\n" : "NO\n"));
		} else {
			par[get(p.second.first)] = get(p.second.second);
		}
	}
	reverse(ans.begin(), ans.end());
	for (auto &p : ans)
		cout << p;

	return 0;
}
