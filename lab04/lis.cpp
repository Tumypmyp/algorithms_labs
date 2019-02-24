#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 401, BIG = 1e9 + 7;



int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n), dp(n), par(n);
	vector<point> min_val(n, {BIG, BIG});
	min_val[0] = {-BIG, 0};
	for (auto &p : a)
		cin >> p;

	int max_i = 0;

	for (int i = 0; i < n; ++i) {
		int ind = int(lower_bound(min_val.begin(), min_val.end(), mp(a[i], 0)) - min_val.begin()) - 1;
		if (ind >= 0 && dp[i] < ind + 1) {
			dp[i] = ind + 1;
			par[i] = min_val[ind].y;
		}
		min_val[ind + 1] = min(min_val[ind + 1], {a[i], i});
		if (dp[max_i] < dp[i])
			max_i = i;
		/*/
		cout << ind << "\n";
		for (int j = 0; j < n; ++j)
			cout << dp[j] << " ";
		cout << "\n";
		for (int j = 0; j < n; ++j)
			cout << min_val[j].x << " " << min_val[j].y << ", ";
		cout << "\n";
		//*/
	}
	int v = max_i;
	vector<int> ans;
	cout << dp[max_i] << "\n";
	for (int i = 0; i < dp[max_i]; ++i) {
		ans.push_back(a[v]);
		v = par[v];
	}
	reverse(ans.begin(), ans.end());
	for (auto &p : ans)
		cout << p << " ";



	return 0;
}
