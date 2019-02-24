#include <bits/stdc++.h>

using namespace std;

mt19937 gen(123);

int kth(vector<int> &a, int k) {
	/*/
	for (auto &p : a)
		cout << p << " ";
	cout << " - " << k << "th\n";
	//*/
	// cout << k << endl;
	if (a.size() == 1) {
		return a[0];
	}
	int mid_v = a[abs(int(gen())) % a.size()];
	vector<int> b1, b2;
	for (auto &p : a)
		if (p < mid_v)
			b1.push_back(p);
		else
			b2.push_back(p);
	a.clear();
	a.shrink_to_fit();
	if (k < (int)b1.size()) {
		b2.clear();
		b2.shrink_to_fit();
		return kth(b1, k);
	} else {
		int b1_sz = (int)b1.size();
		b1.clear();
		b1.shrink_to_fit();
		return kth(b2, k - b1_sz);
	}
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, k, A, B, C;
	cin >> n >> k;
	vector<int> a(max(2, n), 2);
	cin >> A >> B >> C >> a[0] >> a[1];
	for (int i = 2; i < n; ++i)
		a[i] = A * a[i - 2] + B * a[i - 1] + C;
	cout << kth(a, k - 1);
	return 0;
}
