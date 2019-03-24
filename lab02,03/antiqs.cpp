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
	for (int i = 0; i < n; i++)
		a[i] = i + 1;
	for (int i = 2; i < n; i++)
		swap(a[i], a[i / 2]);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	return 0;
}
