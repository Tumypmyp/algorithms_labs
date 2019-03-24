#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 401, BIG = 1e9 + 7;

struct meeting{
	int L, R, c;
};

bool getb(int a, int ind) {
	return (a >> ind) & 1;
}

int invb(int a, int ind) {
	return a ^ (1 << ind);
}

int get_num(int a, int n) {
	int ans = 0;
	for (int i = 0; i < n; ++i)
		ans += getb(a, i);
	return ans;
}

void out_mask(int a, int n, string s = " ") {
	for (int i = 0; i < n; ++i)
		cout << getb(a, i);
	cout << s;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("meetings.in", "r", stdin), freopen("meetings.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n, k;
	cin >> n >> k;
	vector<int> dp(1 << n, BIG), par(1 << n, -1);
	vector<meeting> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i].L >> a[i].R >> a[i].c;

	dp[0] = k;
	int max_mask = 0;
	for (int mask = 0; mask < (1 << n); ++mask) {
		for (int i = 0; i < n; ++i)
			if (!getb(mask, i) && a[i].L <= dp[mask] && dp[mask] <= a[i].R) {
				dp[invb(mask, i)] = dp[mask] + a[i].c;
				par[invb(mask, i)] = i;
			}
		if (dp[mask] < BIG && get_num(max_mask, n) < get_num(mask, n))
			max_mask = mask;
		// out_mask(mask, n);
		// cout << dp[mask] << " " << par[mask] << "\n";
	}

	// out_mask(max_mask, n, "\n");
	vector<int> ans;
	while (max_mask > 0) {
		ans.push_back(par[max_mask]);
		max_mask = invb(max_mask, par[max_mask]);
	}
	cout << ans.size() << "\n";
	reverse(ans.begin(), ans.end());
	for (auto &p : ans)
		cout << p + 1 << " ";

	return 0;
}
