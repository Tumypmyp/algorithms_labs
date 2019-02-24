#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll N = 5e3, BIG = 2e18 + 7, MOD = 1e9;


void upd(int &a, int b) {
	a = max(a, b);
}

int x, a, y, b, l;

bool can(int w) {
	vector<vector<int>> dp(x * 2, vector<int> (y * 2));
	for (int i = 0; i <= x; ++i)
		for (int j = 0; j <= y; ++j)
			for (int i2 = 0; i + i2 <= x && i2 * a - a <= w; ++i2) {
				int j2 = w - i2 * a;
				if (j2 < 0)
					j2 = 0;
				else
					j2 = j2 / b + (j2 % b != 0);
				// cout << i2 << " " << j2 << "\n";
				if (j + j2 <= y)
					upd(dp[i + i2][j + j2], dp[i][j] + 1);
			}
	/*/
	cout << w << "\n";
	for (int i = 0; i <= x; ++i) {
		for (int j = 0; j <= y; ++j)
			cout << dp[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	//*/
	int ans = 0;
	for (int i = 0; i <= x; ++i)
		for (int j = 0; j <= y; ++j)
			upd(ans, dp[i][j]);
	return ans >= l;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("bridge.in", "r", stdin), freopen("bridge.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> x >> a >> y >> b >> l;
	int L = 0, R = x * a + y * b + 1, mid;
	// can(8);
	// return 0;
	while (L + 1 < R) {
		mid = (L + R) / 2;
		if (can(mid))
			L = mid;
		else
			R = mid;
	}
	cout << L;
	return 0;
}
