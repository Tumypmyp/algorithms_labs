#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll N = 5e3, BIG = 2e18 + 7, MOD = 1e9;


vector<ll> a, pref;

ll get_pref(ll x) {
	return x >= 0 ? pref[x] : 0;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("optimalcode.in", "r", stdin), freopen("optimalcode.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n;
	cin >> n;
	a.resize(n);
	pref.resize(n);
	for (auto &p : a)
		cin >> p;
	for (ll i = 0; i < n; ++i)
		pref[i] = (i > 0 ? pref[i - 1] : 0) + a[i];

	vector<vector<ll>> dp(n + 1, vector<ll> (n + 1));
	auto par = dp;

	for (ll L = 0; L < n; ++L)
		par[L][L + 1] = L;

	for (ll d = 2; d <= n; ++d) {
		for (ll L = 0, R = L + d; R <= n; ++L, ++R) {
			dp[L][R] = BIG;
			for (ll mid = par[L][R - 1]; mid <= par[L + 1][R]; ++mid) {
				if (dp[L][R] > dp[L][mid] + dp[mid][R]) {
					dp[L][R] = dp[L][mid] + dp[mid][R];
					par[L][R] = mid;
				}
			}
			// cout << dp[L][R] << " min dp LR\n";
			// cout << L << " " << R << " += " << get_pref(R - 1) - get_pref(L - 1) << endl;
			dp[L][R] += get_pref(R - 1) - get_pref(L - 1);
		}
	}

	/*/
	cout << "\n";
	for (ll i = 0; i <= n; ++i) {
		for (ll j = 0; j <= n; ++j)
			cout << dp[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	for (ll i = 0; i <= n; ++i) {
		for (ll j = 0; j <= n; ++j)
			cout << par[i][j] << " ";
		cout << "\n";
	}
	//*/
	cout << dp[0][n] << "\n";
	for (ll i = 0; i < n; ++i) {
		ll L = 0, R = n;
		vector<ll> ans;
		while (L + 1 < R) {
			if (par[L][R] <= i) {
				ans.push_back(1);
				L = par[L][R];
			} else {
				ans.push_back(0);
				R = par[L][R];
			}
			// cout << L << " " << R << endl;
		}
		for (auto &p : ans)
			cout << p;
		cout << "\n";
	}
	return 0;
}
