#include <bits/stdc++.h>

using namespace std;



int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	int m, x, L, R, mid;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> x;
		int ans_L, ans_R;
		L = -1, R = n;
		while (L + 1 < R) {
			mid = (L + R) / 2;
			if (a[mid] < x)
				L = mid;
			else
				R = mid;
		}
		ans_L = R;
		L = -1, R = n;
		while (L + 1 < R) {
			mid = (L + R) / 2;
			if (a[mid] > x)
				R = mid;
			else
				L = mid;
		}
		ans_R = L;
		if (ans_R - ans_L + 1 == 0)
			cout << "-1 -1\n";
		else
			cout << ans_L + 1 << " " << ans_R + 1 << "\n";
	}
	return 0;
}
