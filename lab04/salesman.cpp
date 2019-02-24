#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<ll, ll>
#define mp make_pair

const ll N = 401, BIG = 1e13 + 7;

bool getb(int a, int ind) {
	return (a >> ind) & 1;
}

int invb(int a, int ind) {
	return a ^ (1 << ind);
}


void out_mask(int a, int n, string s = "") {
	for (int i = 0; i < n; ++i)
		cout << getb(a, i);
	cout << s;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("salesman.in", "r", stdin), freopen("salesman.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n, m;
	cin >> n >> m;
	vector<vector<ll>> dp(1 << n, vector<ll> (n, BIG));
	vector<vector<ll>> gr(n, vector<ll> (n, BIG));

	ll fr, to, w;
	for (int i = 0; i < m; ++i) {
		cin >> fr >> to >> w, --to, --fr;
		gr[to][fr] = gr[fr][to] = w;
	}
	for (int i = 0; i < n; ++i)
		dp[invb(0, i)][i] = 0;

	for (int mask = 0; mask < (1 << n); ++mask) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (getb(mask, i) && !getb(mask, j) && gr[i][j] < BIG) {
					dp[invb(mask, j)][j] = min(dp[invb(mask, j)][j], dp[mask][i] + gr[i][j]);
			}
	}
	/*/
	for (int mask = 1; mask < (1 << n); ++mask) {
		out_mask(mask, n, "\n");
		for (int i = 0; i < n; ++i)
			cout << i << ": " << dp[mask][i] << "\n";
		cout << "\n\n";
	}
	//*/
	ll ans = BIG;
	for (int i = 0; i < n; ++i)
		ans = min(ans, dp[(1 << n) - 1][i]);
	cout << (ans < BIG ? ans : -1);
	return 0;
}
