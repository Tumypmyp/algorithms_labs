#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll N = 5e3, BIG = 2e18 + 7, MOD = 999999937;


void out(vector<vector<ll>> a) {
	for (auto &v : a) {
		for (auto &p : v)
			cout << p << " ";
		cout << "\n";
	}
	cout << "\n";
}
const vector<vector<ll>> matrix =
	{{1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1},
	{1, 1, 0, 1, 0},
	{1, 1, 0, 1, 0}};
const vector<vector<ll>> one =
	{{1, 0, 0, 0, 0},
	{0, 1, 0, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1}};

vector<vector<ll>> mult(vector<vector<ll>> a, vector<vector<ll>> b) {
	// out(a);
	// out(b);
	// cout << "\nnow mult\n";
	vector<vector<ll>> ans(a.size(), vector<ll> (b[0].size()));
	for (int i = 0; i < (int)ans.size(); ++i)
		for (int j = 0; j < (int)ans[i].size(); ++j) {
			for (int u = 0; u < (int)b.size(); ++u) {
				ans[i][j] += a[i][u] * b[u][j];
				ans[i][j] %= MOD;
			}
			// out(ans);
		}
	return ans;
}

vector<vector<ll>> pow(ll x) {
	if (x == 0)
		return one;
	auto sq = pow(x / 2);
	sq = mult(sq, sq);
	if (x % 2 != 0)
		sq = mult(sq, matrix);
	return sq;
}

void solve(ll n) {
	// vector<vector<ll>> a(1, vector<ll> (5, 1));
	vector<vector<ll>> a(5, vector<ll> (1, 1));
	// out(a);
	// out(mult(matrix, matrix));
	// out(pow(2));
	auto ans = mult(pow(n - 1), a);
	//*/
	// out(ans);
	ll sum = 0;
	for (int i = 0; i < (int)ans.size(); ++i) {
		sum += ans[i][0];
		sum %= MOD;
	}
	cout << sum << "\n";
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("sequences.in", "r", stdin), freopen("sequences.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n;
	while (cin >> n) {
		if (n == 0)
			break;
		solve(n);
	}
	return 0;
}
