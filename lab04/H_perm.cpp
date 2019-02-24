#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 401, BIG = 1e9 + 7;

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

int gcd(int a, int b) {
	while (a > 0) {
		b %= a;
		swap(a, b);
	}
	return b;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("perm.in", "r", stdin), freopen("perm.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n, m, k;
	cin >> n >> m >> k, --m;
	vector<vector<ll>> dp(1 << n, vector<ll> (n));
	vector<int> a(n);

	for (auto &p : a)
		cin >> p;
	sort(a.begin(), a.end());
	for (int i = 0; i < n; ++i)
		dp[invb(0, i)][i] = 1;

	for (int mask = 0; mask < (1 << n); ++mask) {
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (getb(mask, i) && !getb(mask, j) && gcd(a[i], a[j]) >= k) {
					dp[invb(mask, j)][j] += dp[mask][i];
				}
	}
	/*/
	for (int mask = 0; mask < (1 << n); ++mask) {
		out_mask(mask, n);
		for (int i = 0; i < n; ++i)
			cout << dp[mask][i] << " ";
		cout << "\n";
	}
	cout << "\n";
	//*/
	vector<int> ans;
	int mask = (1 << n) - 1;

	ll sum = 0;
	for (int i = 0; i < n; ++i)
		sum += dp[mask][i];
	if (sum <= m) {
		cout << -1;
		return 0;
	}
	for (int i = 0; i < n;) {
		for (int j = 0; j < n; ++j) {
			if (!getb(mask, j) || (!ans.empty() && gcd(a[ans.back()], a[j]) < k))
				continue;
			if (m < dp[mask][j]) {
				ans.push_back(j);
				mask = invb(mask, j);
				++i;
				break;
			} else {
				m -= dp[mask][j];
			}
		}
		/*/
		for (auto &p : ans)
			cout << p << " ";
		cout << endl;
		//*/
	}
	if (m > 0) {
		cout << -1;
		return 0;
	}
	for (auto &p : ans)
		cout << a[p] << " ";
	/*/
	for (int mask = 1; mask < (1 << n); ++mask) {
		out_mask(mask, n, "\n");
		for (int i = 0; i < n; ++i)
			cout << i << ": " << dp[mask][i] << "\n";
		cout << "\n\n";
	}
	//*/

	return 0;
}
