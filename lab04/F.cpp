#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll N = 1e4 + 3, BIG = 1e9 + 7, MOD = 1e9;


string a, b;
bool dp[N][N], pref[N];


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	dp[0][0] = true;
	getline(cin, a);
	getline(cin, b);
	for (int i = 0; i <= (int)a.size(); ++i)
		for (int j = 0; j <= (int)b.size(); ++j) {
			if (a[i] == '*' && dp[i][j])
				dp[i + 1][j] = true;
			if (i > 0 && a[i - 1] == '*' && dp[i][j])
				dp[i][j + 1] = true;
			if (a[i] == '?' && dp[i][j])
				dp[i + 1][j + 1] = true;
			if (a[i] == b[j] && dp[i][j])
				dp[i + 1][j + 1] = true;
		}
	/*/
	for (int i = 0; i <= a.size(); ++i) {
		for (int j = 0; j <= b.size(); ++j)
			cout << dp[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	//*/
	cout << (dp[(int)a.size()][(int)b.size()] ? "YES" : "NO");

	return 0;
}
