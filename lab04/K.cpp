#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll N = 5e3, BIG = 1e9 + 7, MOD = 1e9;

ll a[N], dp[N][N];


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		dp[i][i] = 1;
	}

	for (int i = 1; i < n; ++i) {
		for (int L = 0, R = L + i; R < n; ++L, ++R) {
			dp[L][R] = dp[L + 1][R] + dp[L][R - 1] - (a[L] == a[R] ? -1LL : dp[L + 1][R - 1]);
			dp[L][R] = ((dp[L][R] % MOD) + MOD) % MOD;
		}
	}

	/*/
	for (int L = 0; L < n; ++L) {
		for (int R = 0; R < n; ++R)
			cout << dp[L][R] << " ";
		cout << "\n";
	}
	//*/
	cout << dp[0][n - 1] % MOD;


	return 0;
}
