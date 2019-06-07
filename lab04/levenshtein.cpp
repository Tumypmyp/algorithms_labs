#include <bits/stdc++.h>
#define ll long long

using namespace std;

const ll MAXN = 5e3 + 3, MAXA = 1e9 + 5;

string s1, s2;
int dp[MAXN][MAXN];

int main() {
	freopen("levenshtein.in", "r", stdin), freopen("levenshtein.out", "w", stdout);
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> s1 >> s2;
	s1 = " " + s1;
	s2 = " " + s2;
	for (int i = 0; i < (int)s1.size(); i++)
		dp[i][0] = i;
	for (int i = 0; i < (int)s2.size(); i++)
		dp[0][i] = i;
	for (int i = 1; i < (int)s1.size(); i++)
		for (int j = 1; j < (int)s2.size(); j++)
			dp[i][j] = min(dp[i - 1][j] + 1,
					min(dp[i][j - 1] + 1,
							s1[i] == s2[j] ?
									dp[i - 1][j - 1] : dp[i - 1][j - 1] + 1));
	/*/
	for (int i = 0; i < s1.size(); i++) {
		for (int j = 0; j < s2.size(); j++)
			cout << dp[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";
	//*/
	cout << dp[s1.size() - 1][s2.size() - 1];
	return 0;
}
