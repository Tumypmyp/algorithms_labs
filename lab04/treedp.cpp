#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<ll, ll>
#define mp make_pair


const ll N = 1103, N2 = N / 9, BIG = 2e9 + 7, MOD = 999999937;


ll n;
vector<ll> tree_sz, tree_sum_way, ans;
vector<vector<point>> gr, ind_edge;

void dfs1(ll v = 0, ll par = -1) {
	for (auto &to : gr[v]) {
		if (to.x == par)
			continue;
		dfs1(to.x, v);
		tree_sz[v] += tree_sz[to.x];
		tree_sum_way[v] += tree_sum_way[to.x] + tree_sz[to.x];
	}
	// cout << v << " " << tree_sz[v] << " " << tree_sum_way[v] << endl;
}

void dfs2(ll v = 0, ll par = -1, ll sum_way_up = 0) {
	for (auto &to : gr[v]) {
		if (to.x == par)
			continue;
		// cout << "\n\n";
		// cout << sum_way_up << " + " << tree_sum_way[v] - tree_sum_way[to.x] - tree_sz[to.x]
			// << " + " << tree_sz[0] - tree_sz[to.x] << "\n";
		ll up = sum_way_up + tree_sum_way[v] - tree_sum_way[to.x] - tree_sz[to.x]
				+ tree_sz[0] - tree_sz[to.x];
		// ans[to.y] = (up + 1) * (tree_sum_way[to.x] + 1) - 1;
		ans[to.y] = up * tree_sz[to.x] + tree_sum_way[to.x] * (tree_sz[0] - tree_sz[to.x]);
		// cout << v << "-" << to.x << " " << up << " up, " << tree_sum_way[to.x]
			// << " down,  ans " << ans[to.y] << "\n";
		dfs2(to.x, v, up);
	}
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("treedp.in", "r", stdin), freopen("treedp.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	gr.resize(n);
	ind_edge.resize(n);
	ll fr, to;
	for (ll i = 0; i < n - 1; ++i) {
		cin >> fr >> to, --fr, --to;
		gr[fr].push_back({to, i});
		gr[to].push_back({fr, i});
	}
	tree_sz.resize(n, 1);
	tree_sum_way.resize(n);
	dfs1();
	ans.resize(n - 1);
	dfs2();
	/*/
	for (ll i = 0; i < n; ++i) {
		cout << i << ": " << tree_sz[i] << " " << tree_sum_way[i] << "\n";
	}
	//*/
	for (auto &p : ans)
		cout << p << " ";
	return 0;
}
