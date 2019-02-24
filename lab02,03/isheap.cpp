#include <bits/stdc++.h>

using namespace std;


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	for (int i = 2; i <= n; ++i)
		if (a[i / 2] > a[i]) {
			cout << "NO";
			return 0;
		}
	cout << "YES";
	return 0;
}
