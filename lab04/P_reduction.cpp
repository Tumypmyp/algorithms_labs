#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define forn(i, n) for (int i = 0; i < int(n); ++i)
#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 401, BIG = 1e9 + 7;

int n;
vector<vector<point>> gr;
vector<vector<int>> dp;
vector<int> ans, par, par_ind;

void dfs(int v) {
	vector<point> son;
	for (auto to : gr[v]) {
		if (to.x == par[v])
			continue;
		par[to.x] = v;
		par_ind[to.x] = to.y;
		dfs(to.x);
		son.push_back(to);
	}

	dp[v][1] = 0;
	// cout << v << ": ";
	for (auto to : son) {
		// cout << to.x << "| ";
		// forn(u, n + 1)
		// 	cout << dp[to.x][u] << " ";
		// cout << " -to\n";
		// forn(u, n + 1)
		// 	cout << dp[v][u] << " ";
		// cout << " -v\n";
		for (int j = 1; j <= n && dp[v][j] < BIG; ++j)
			++dp[v][j];

		// forn(u, n + 1)
		// 	cout << dp[v][u] << " ";
		// cout << "\n";

		auto ans = dp[v];
		for (int i = 1; i <= n && dp[to.x][i] < BIG; ++i) {
			for (int j = 1; j <= n && dp[v][j] < BIG; ++j)
				ans[i + j] = min(dp[v][i + j], dp[to.x][i] + dp[v][j] - 1);

			// forn(u, n + 1)
			// 	cout << ans[u] << " ";
			// cout << "\n";
		}
		dp[v] = ans;
	}
	// cout << "\n";
}

void get_ans(int v, int p) {
	vector<point> son;
	for (auto to : gr[v]) {
		if (to.x == par[v])
			continue;
		son.push_back(to);
	}

	dp[v][1] = 0;
	// cout << v << ": " << endl;
	vector<vector<int>> dp2(son.size() + 1, vector<int> (n + 1, BIG));
	vector<vector<point>> pr(son.size() + 1, vector<point> (n + 1));

	dp2[0][1] = 0;
	for (int u = 0; u < (int)son.size(); ++u) {
		auto to = son[u];

		// cout << to.x << "| ";
		// forn(u2, n + 1)
		// 	cout << dp[to.x][u2] << " ";
		// cout << " -to\n";
		// forn(u2, n + 1)
		// 	cout << dp2[u][u2] << " ";
		// cout << " -v\n";

		// for (int j = 1; j <= n && dp2[u][j] < BIG; ++j)
		// 	dp2[u + 1][j] = dp2[u][j] + 1;
		dp2[u + 1][1] = dp2[u][1] + 1;
		pr[u + 1][1] = {1, to.y};
		for (int i = 1; i <= n && dp[to.x][i] < BIG; ++i) {
			for (int j = 1; j <= n && dp2[u][j] < BIG; ++j)
				if (dp2[u + 1][i + j] > dp[to.x][i] + dp2[u][j]) {
					dp2[u + 1][i + j] = dp[to.x][i] + dp2[u][j];
					pr[u + 1][i + j] = {j, to.y};
				}

			// forn(u2, n + 1)
			// 	cout << dp2[u + 1][u2] << " ";
			// cout << endl;
		}
	}

	/*/
	cout << "\n";
	cout << v << " " << p << " : \n";
	for (int i = 0; i < son.size() + 1; ++i) {
		for (int j = 0; j <= n; ++j)
			cout << dp2[i][j] << " ";
		cout << "\n";
	}
	cout << " - dp\n";
	for (int i = 0; i < son.size() + 1; ++i) {
		for (int j = 0; j <= n; ++j)
			cout << pr[i][j].x << "\t";
		cout << "\n";
	}
	cout << "- par\n" << endl;
	//*/
	int x = (int)son.size(), y = p;
	vector<pair<int, point>> all_ans;
	while (dp2[x][y] > 0) {
		// cout << x << " " << y << endl;
		if (pr[x][y].y > 0) {
			if (y - pr[x][y].x > 0) {
				all_ans.push_back(mp(son[x - 1].x, mp(y - pr[x][y].x, v)));
			} else {
				ans.push_back(son[x - 1].y);
				// cout << "added " << son[x - 1].y << "\n";
			}
			y = pr[x][y].x;
		}
		x--;
	}
	/*/
	for (auto &p2 : all_ans)
		cout << p2.x << " " << p2.y.x << " " << p2.y.y << "\n";
	cout << " - new ans" << endl;
	//*/
	for (auto &p2 : all_ans)
		get_ans(p2.x, p2.y.x);
	dp[v] = dp2.back();
	// cout << "\n";
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("perm.in", "r", stdin), freopen("perm.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int fr, to, p;
	cin >> n >> p;
	gr.resize(n);
	dp.resize(n, vector<int> (n + 1, BIG));
	par.resize(n, -1);
	par_ind.resize(n, -1);

	for (int i = 0; i < n - 1; ++i) {
		cin >> fr >> to, --fr, --to;
		gr[fr].push_back({to, i + 1});
		gr[to].push_back({fr, i + 1});
	}
	dfs(0);
	//*/
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= n; ++j)
			cout << dp[i][j] << " ";
		cout << endl;
	}
	//*/
	int min_x = 1;
	for (int i = 1; i < n; ++i)
		if (dp[min_x][p] > dp[i][p])
			min_x = i;
	if (min_x >= n || dp[min_x][p] + 1 > dp[0][p])
		min_x = 0;
	get_ans(min_x, p);
	if (min_x > 0)
		ans.push_back(par_ind[min_x]);
	cout << min_x << endl;
	cout << ans.size() << "\n";
	for (auto &p2 : ans)
		cout << p2 << " ";
	return 0;
}
