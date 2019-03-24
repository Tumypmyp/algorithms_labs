#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<char, int>
#define mp make_pair
#pragma GCC optimize("O3")

const int N = 1103, N2 = N / 9, BIG = 2e9 + 7, MOD = 999999937;


// not accepted

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("number.in", "r", stdin), freopen("number.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> pows(n, 1);
	for (int i = 1; i < n; ++i)
		pows[i] = (pows[i - 1] * 10) % n;

	vector<vector<vector<bool>>> dp(n / 9 + 10, vector<vector<bool>> (n + 1, vector<bool>(n)));
	vector<vector<vector<char>>> par(N2, vector<vector<char>> (n + 1, vector<char>(n, 10)));
	dp[0][0][0] = true;

	for (int i = 1; i < (int)dp.size(); ++i) {
		for (int j = 0; j <= n; ++j)
			for (int u = 0; u < n; ++u)
				for (char p = 0; p < 10 && p <= j; ++p) {
					// cout << i << " " << j << " " << u << " " << (int)p << endl;
					// cout << ((u - pows[i] * p) % n + n) % n << endl;
					if (dp[i - 1][j - p][((u - pows[i - 1] * p) % n + n) % n]) {
						dp[i][j][u] = true;
						par[i][j][u] = p;
						break;
					}
				}
		/*/
		cout << i << " :\n";
		for (int j = 0; j <= n; ++j) {
			for (int u = 0; u < n; ++u)
				cout << dp[i][j][u] << " ";
			cout << endl;
		}
		cout << endl;
		//*/
		if (dp[i][n][0]) {
			// cout << "found" << endl;
			vector<int> ans;
			int x = i, y = n, z = 0;
			while (x > 0) {
				auto p = par[x][y][z];
				// cout << x << " " << y << " " << z << "  " << (int)p << endl	;
				ans.push_back(p);
				y -= p;
				z = ((z - p * pows[x - 1]) % n + n) % n;
				--x;
			}
			// reverse(ans.begin(), ans.end());
			for (auto &ch : ans)
				cout << ch;
			cout << "\n";
			return 0;
		}
	}
	return 0;
}
