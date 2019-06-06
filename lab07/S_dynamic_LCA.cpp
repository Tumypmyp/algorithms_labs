#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9;



int timer;
vector<vector<int>> gr;
vector<int> d, tin, tout, lg;
vector<point> all;

void dfs(int v = 0, int d2 = 0, int p = -1) {
	tin[v] = timer++;
	d[v] = d2;
	all.push_back({d2, v});
	for (auto &to : gr[v]) {
		if (to == p)
			continue;
		dfs(to, d2 + 1, v);
		all.push_back({d2, v});
	}
	tout[v] = timer++;
}

int get_lca(vector<vector<point>> &dp, int x, int y) {
	ll v1 = tin[x], v2 = tin[y];
	if (v1 > v2)
		swap(v1, v2);
	++v2;
	ll d = v2 - v1;
	return min(dp[v1][lg[d]], dp[v2 - (1 << lg[d])][lg[d]]).y;
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	while(cin >> n) {
		if (n == 0)
			break;
		int x, y;
		vector<point> q;

		gr.assign(n, vector<int>());
		for (int i = 1; i < n; ++i) {
			cin >> x >> y, --x, --y;
			gr[x].push_back(y);
			gr[y].push_back(x);
		}
		d.assign(n, 0);
		tin.assign(n, 0);
		tout.assign(n, 0);
		all.clear();
		timer = 0;
		dfs();

		int n2 = (int)all.size();

		lg.resize(n2 + 1);
		for (int i = 2; i <= n2; ++i)
			lg[i] = lg[i / 2] + 1;

		vector<vector<point>> a(n2, vector<point> (lg[n2] + 1));
		for (int i = 0; i < n2; ++i)
			a[i][0] = all[i];

		for (int d = 0; d < (int)a[0].size() - 1; ++d) {
			for (int i = 0; i < n2; ++i)
				if (i + (1 << d) < n2)
					a[i][d + 1] = min(a[i][d], a[i + (1 << d)][d]);
		}

		cin >> m;
		int root = 0;
		char t;
		for (int i = 0; i < m; ++i) {
			cin >> t >> x, --x;
			if (t == '!') {
				root = x;
			} else {
				cin >> y, --y;
				vector<int> v;
				v.push_back(get_lca(a, x, y));
				v.push_back(get_lca(a, root, y));
				v.push_back(get_lca(a, root, x));
				// for (auto &p : v)
				// 	cout << p << " ";
				// cout << "\n";
				sort(v.begin(), v.end());
				int ans = (v[0] == v[1] ? v[2] : v[0]);
				cout << ans + 1 << "\n";
			}
		}
	}
	return 0;
}
