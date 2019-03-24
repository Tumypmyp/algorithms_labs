#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<ll, ll>
#define mp make_pair

const int N = 401, BIG = 1e9 + 7;


int n;
vector<point> dp;
vector<vector<point>> gr;

void dfs(int v, int par = -1) {
	ll sum = 0, max_dif = -BIG;
	for (auto &to : gr[v]) {
		if (to.x == par)
			continue;
		dfs((int)to.x, v);
		sum += dp[to.x].x;
		max_dif = max(max_dif, dp[to.x].y - dp[to.x].x + to.y);
	}
	dp[v].y = sum;
	dp[v].x = max(sum, sum + max_dif);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("matching.in", "r", stdin), freopen("matching.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	gr.resize(n);
	dp.resize(n);
	ll fr, to, w;
	for (int i = 0; i < n - 1; ++i) {
		cin >> fr >> to >> w, --to, --fr;
		gr[fr].push_back({to, w});
		gr[to].push_back({fr, w});
	}

	dfs(0);
	cout << dp[0].x;
	return 0;
}
