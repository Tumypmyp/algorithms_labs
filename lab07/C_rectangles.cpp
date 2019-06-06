#include <bits/stdc++.h>
// #pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 130, lg_N = 9, BIG = 1e9 + 7, MOD = 1e9 + 7;

int dp_L[N][N][lg_N][lg_N], dp_R[N][N][lg_N][lg_N];
int dp_U[N][N][lg_N][lg_N], dp_D[N][N][lg_N][lg_N];
int n, m;
vector<int> lg;

void pre_calc(int dp[N][N][lg_N][lg_N]) {
	for (int d_j = 1; d_j < lg_N; ++d_j)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < m; ++j) {
				if (j + (1 << (d_j - 1)) >= m)
					continue;
				dp[i][j][0][d_j] = min(dp[i][j][0][d_j - 1],
					dp[i][j + (1 << (d_j - 1))][0][d_j - 1]);
			}
	for (int d_i = 1; d_i < lg_N; ++d_i)
		for (int d_j = 0; d_j < lg_N; ++d_j)
		 	for (int i = 0; i < n; ++i)
		 		for (int j = 0; j < m; ++j) {
		 			if (i + (1 << (d_i - 1)) >= n)
		 				continue;
		 			dp[i][j][d_i][d_j] = min(dp[i][j][d_i - 1][d_j],
		 				dp[i + (1 << (d_i - 1))][j][d_i - 1][d_j]);
		 		}
}

int get_min(const int dp[N][N][lg_N][lg_N], vector<int> v) {
	++v[2], ++v[3];
	int d_i = lg[v[2] - v[0]], d_j = lg[v[3] - v[1]];
	int ans = dp[v[0]][v[1]][d_i][d_j];
	ans = min(ans, dp[v[0]][v[3] - (1 << d_j)][d_i][d_j]);
	ans = min(ans, dp[v[2] - (1 << d_i)][v[1]][d_i][d_j]);
	ans = min(ans, dp[v[2] - (1 << d_i)][v[3] - (1 << d_j)][d_i][d_j]);
	return ans;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	lg.resize(N);
	for (int i = 2; i < N; ++i)
		lg[i] = lg[i / 2] + 1;

	cin >> n >> m;
	point p1, p2;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			cin >> p1.x >> p1.y >> p2.x >> p2.y;
			if (p1.x > p2.x)
				swap(p1.x, p2.x);
			if (p1.y > p2.y)
				swap(p1.y, p2.y);
			dp_L[i][j][0][0] = -p1.x;
			dp_R[i][j][0][0] = p2.x;
			dp_D[i][j][0][0] = -p1.y;
			dp_U[i][j][0][0] = p2.y;
		}
	pre_calc(dp_L);
	pre_calc(dp_D);
	pre_calc(dp_R);
	pre_calc(dp_U);
	/*/
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			cout << i << " " << j << ": ";
			for (int d_i = 0; d_i < 3; ++d_i)
				for (int d_j = 0; d_j < 3; ++d_j)
					cout << d_i << " " << d_j << " - " << dp_L[i][j][d_i][d_j] << "; ";
			cout << "\n";
		}

	//*/
	ll q, A, B, v0, sum = 0;
	cin >> q >> A >> B >> v0;
	for (int i = 0; i < q; ++i) {
		vector<int> v(4);
		for (auto &p : v) {
			v0 = (A * v0 + B) % MOD;
			p = (int)v0;
		}
		v[0] %= n;
		v[1] %= m;
		v[2] %= n;
		v[3] %= m;
		if (v[0] > v[2])
			swap(v[0], v[2]);
		if (v[1] > v[3])
			swap(v[1], v[3]);
		// ll L = -get_min(dp_L, v);
		// ll R = get_min(dp_R, v);
		// ll D = -get_min(dp_D, v);
		// ll U = get_min(dp_U, v);
		++v[2], ++v[3];
		int d_i = lg[v[2] - v[0]], d_j = lg[v[3] - v[1]];

		int ans_L = dp_L[v[0]][v[1]][d_i][d_j];
		ans_L = min(ans_L, dp_L[v[0]][v[3] - (1 << d_j)][d_i][d_j]);
		ans_L = min(ans_L, dp_L[v[2] - (1 << d_i)][v[1]][d_i][d_j]);
		ans_L = min(ans_L, dp_L[v[2] - (1 << d_i)][v[3] - (1 << d_j)][d_i][d_j]);
		ans_L *= -1;

		int ans_R = dp_R[v[0]][v[1]][d_i][d_j];
		ans_R = min(ans_R, dp_R[v[0]][v[3] - (1 << d_j)][d_i][d_j]);
		ans_R = min(ans_R, dp_R[v[2] - (1 << d_i)][v[1]][d_i][d_j]);
		ans_R = min(ans_R, dp_R[v[2] - (1 << d_i)][v[3] - (1 << d_j)][d_i][d_j]);

		int ans_D = dp_D[v[0]][v[1]][d_i][d_j];
		ans_D = min(ans_D, dp_D[v[0]][v[3] - (1 << d_j)][d_i][d_j]);
		ans_D = min(ans_D, dp_D[v[2] - (1 << d_i)][v[1]][d_i][d_j]);
		ans_D = min(ans_D, dp_D[v[2] - (1 << d_i)][v[3] - (1 << d_j)][d_i][d_j]);
		ans_D *= -1;

		int ans_U = dp_U[v[0]][v[1]][d_i][d_j];
		ans_U = min(ans_U, dp_U[v[0]][v[3] - (1 << d_j)][d_i][d_j]);
		ans_U = min(ans_U, dp_U[v[2] - (1 << d_i)][v[1]][d_i][d_j]);
		ans_U = min(ans_U, dp_U[v[2] - (1 << d_i)][v[3] - (1 << d_j)][d_i][d_j]);

		if (ans_L > ans_R || ans_D > ans_U)
			continue;
		sum += ((ll)ans_R - ans_L) * ((ll)ans_U - ans_D);
		sum %= MOD;
	}
	cout << sum;
	return 0;
}
