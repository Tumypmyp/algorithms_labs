#include <bits/stdc++.h>

using namespace std;


void merge_sort(vector<int> &a, int L, int R) {
	if (L + 1 >= R)
		return;
	int mid = (L + R) / 2;
	merge_sort(a, L, mid);
	merge_sort(a, mid, R);
	int i = L, j = mid;
	vector<int> b;
	while (i < mid && j < R) {
		if (a[i] < a[j])
			b.push_back(a[i++]);
		else
			b.push_back(a[j++]);
	}
	while (i < mid) {
		b.push_back(a[i++]);
	}
	while (j < R) {
		b.push_back(a[j++]);
	}


	for (int i = 0; i < (int)b.size(); ++i)
		a[L + i] = b[i];
}

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
	merge_sort(a, 0, n);
	for (int i = 0; i < n; ++i)
		cout << a[i] << " ";
	return 0;
}
