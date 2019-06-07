#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<ll, ll>

const ll N = 401, BIG = 1e15 + 7;

void upd(ll &a, ll b) {
	a = min(a, b);
}

vector<vector<bool>> solved;
vector<vector<ll>> dp;
vector<point> a;


ll get_dp(ll L, ll d) {
	if (solved[L][d])
		return dp[L][d];
	solved[L][d] = true;

	for (ll d1 = 1; d1 < d; d1++) {
		upd(dp[L][d], get_dp(L, d1) + get_dp(L + d1, d - d1) +
				a[L].x * a[L + d1].x * a[L + d - 1].y);
		// cout << "upd " << L << " " << d << " by " << L << " " << d1 << " "
		// 		<< " and " << L + d1 << " " << d - d1 << " + "
		// 			<< a[L].x << " * " << a[L + d1].x << " * " << a[L + d - 1].y << "\n";
	}

	return dp[L][d];
}

void out_solve(ll L, ll d) {
	if (d == 1) {
		cout << "A";
		return;
	}
	for (ll d1 = 1; d1 < d; d1++)
		if (get_dp(L, d) == get_dp(L, d1) + get_dp(L + d1, d - d1)
				+ a[L].x * a[L + d1].x * a[L + d - 1].y) {
			cout << "(";
			out_solve(L, d1);
			out_solve(L + d1, d - d1);
			cout << ")";
			return;
		}
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("matrix.in", "r", stdin), freopen("matrix.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n;
	cin >> n;
	a.resize(n);
	dp.resize(n, vector<ll> (n + 1, BIG));
	solved.resize(n, vector<bool> (n + 1));
	for (auto &p : a)
		cin >> p.x >> p.y;

	for (ll L = 0; L < n; ++L)
		dp[L][1] = 0;

	out_solve(0, n);

	/*/
	cout << "\n";
	for (ll L = 0; L < n; ++L) {
		for (ll d = 0; d <= n; ++d)
			cout << dp[L][d] << " ";
		cout << "\n";
	}
	cout << "\n";
	//*/
	return 0;
}
