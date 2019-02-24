#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 5e3, BIG = 1e9 + 7, MOD = 1e9;


void out_vector(vector<char> v) {
	for (auto &p : v)
		cout << p;
	cout << endl;
}

void upd(int &a, int b) {
	a = max(a, b);
}

vector<int> get_dp(vector<char> a, vector<char> b) {
	int n = (int)a.size(), m = (int)b.size();
	vector<vector<int>> dp(n + 1);
	dp[0] = dp[1] = vector<int> (m + 1);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			upd(dp[i][j], dp[i - 1][j]);
			upd(dp[i][j], dp[i][j - 1]);
			if (a[i - 1] == b[j - 1])
				upd(dp[i][j], dp[i - 1][j - 1] + 1);
		}
		dp[i - 1].clear();
		dp[i - 1].shrink_to_fit();
		if (i < n)
			dp[i + 1].resize(m + 1);
	}
	return dp[n];
}

vector<char> solve(vector<char> a, vector<char> b) {
	if (a.empty() || b.empty())
		return {};
	if ((int)a.size() == 1) {
		for (auto &p : b)
			if (a[0] == p)
				return {a[0]};
		return {};
	}

	vector<char> a1((int)a.size() / 2);
	copy(a.begin(), a.begin() + (int)a1.size(), a1.begin());
	auto ans1 = get_dp(a1, b);

	vector<char> a2_rev((int)a.size() - (int)a1.size());
	copy(a.begin() + (int)a1.size(), a.end(), a2_rev.rbegin());
	vector<char> b_rev(b.size());
	copy(b.begin(), b.end(), b_rev.rbegin());
	auto ans2 = get_dp(a2_rev, b_rev);
	/*/
	for (auto &p : ans1)
		cout << p << " ";
	cout << " ans1\n";
	for (auto &p : ans2)
		cout << p << " ";
	cout << "ans2 \n";
	//*/
	int max_i = 0, max_v = -BIG;
	for (int i = 0; i < (int)ans1.size(); ++i)
		if (max_v < ans1[i] + ans2[(int)ans2.size() - 1 - i]) {
			max_i = i;
			max_v = ans1[i] + ans2[(int)ans2.size() - 1 - i];
		}

	vector<char> b1(max_i);
	copy(b.begin(), b.begin() + (int)b1.size(), b1.begin());
	auto last_ans1 = solve(a1, b1);

	vector<char> b2((int)b.size() - (int)b1.size());
	copy(b.begin() + (int)b1.size(), b.end(), b2.begin());
	vector<char> a2((int)a.size() - (int)a1.size());
	copy(a.begin() + (int)a1.size(), a.end(), a2.begin());

	auto last_ans2 = solve(a2, b2);

	auto last_ans = last_ans1;
	last_ans.resize((int)last_ans.size() + (int)last_ans2.size());
	copy(last_ans2.begin(), last_ans2.end(), last_ans.begin() + last_ans1.size());
	/*/
	cout << "\n";
	out_vector(a);
	out_vector(b);
	out_vector(last_ans);
	cout << "ans\n" << endl;
	//*/
	return last_ans;
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string a2, b2;
	cin >> a2 >> b2;
	int n = (int)a2.size(), m = (int)b2.size();
	vector<char> a(n), b(m);
	for (int i = 0; i < n; ++i)
		a[i] = a2[i];
	for (int i = 0; i < m; ++i)
		b[i] = b2[i];


	auto ans = solve(a, b);
	for (auto &p : ans)
		cout << p;
	/*/
	for (int L = 0; L <= n; ++L) {
		for (int R = 0; R <= m; ++R)
			cout << dp[L][R] << " ";
		cout << "\n";
	}
	//*/

	//*/
	return 0;
}
