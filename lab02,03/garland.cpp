#include <bits/stdc++.h>

using namespace std;

int n;
vector<double> h;

bool ok(double h1) {
	h[1] = h1;
	for (int i = 2; i < n; ++i)
		h[i] = (h[i - 1] + 1) * 2 - h[i - 2];
	for (int i = 0; i < n; ++i)
		if (h[i] <= 0)
			return false;
	return true;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n;
	h.resize(n);
	cin >> h[0];
	cout << setprecision(13) << fixed;
	double L = 0, R = 2e3, mid;
	for (int i = 0; i < 1e3; ++i) {
		mid = (L + R) / 2;
		if (ok(mid))
			R = mid;
		else
			L = mid;
	}
	ok(R);
	cout << h[n - 1];
	return 0;
}
