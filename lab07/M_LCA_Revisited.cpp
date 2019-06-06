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
vector<int> d, tin, tout;
vector<point> all;

void dfs(int v = 0, int d2 = 0) {
	tin[v] = timer++;
	d[v] = d2;
	all.push_back({d2, v});
	for (auto &to : gr[v]) {
		dfs(to, d2 + 1);
		all.push_back({d2, v});
	}
	tout[v] = timer++;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n, m;
	cin >> n >> m;
	int x, y, z;
	vector<point> q;
	gr.resize(n);
	for (int i = 1; i < n; ++i) {
		cin >> x;
		gr[x].push_back(i);
	}
	d.resize(n);
	tin.resize(n);
	tout.resize(n);
	dfs();

	int n2 = (int)all.size();

	vector<int> lg(n2 + 1);
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

	ll a1, a2, ans = 0, a3, a4, sum = 0;
	cin >> a1 >> a2 >> x >> y >> z;
	for (int i = 0; i < m; ++i) {
		// cout << a1 + ans << " " << a2 << "\n";
		ll v1 = tin[(a1 + ans) % n], v2 = tin[a2];
		if (v1 > v2)
			swap(v1, v2);
		++v2;
		ll d = v2 - v1;
		ans = min(a[v1][lg[d]], a[v2 - (1 << lg[d])][lg[d]]).y;
		// cout << ans << "- ans\n";
		sum += ans;
		a3 = (x * a1 + y * a2 + z) % n;
		a4 = (x * a2 + y * a3 + z) % n;
		a1 = a3;
		a2 = a4;
	}
	cout << sum;
	return 0;
}
