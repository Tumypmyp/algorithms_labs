#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll ans = 0, n, m;

unsigned int a0, b0;

unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a0 + b0;
	return cur >> 8;
}

void merge_sort(vector<ll> &a, ll L, ll R) {
	if (L + 1 >= R)
		return;
	ll mid = (L + R) / 2;
	merge_sort(a, L, mid);
	merge_sort(a, mid, R);
	ll i = L, j = mid;
	vector<ll> b;
	while (i < mid && j < R) {
		if (a[i] <= a[j]) {
			b.push_back(a[i++]);
		} else {
			ans += mid - i;
			b.push_back(a[j++]);
		}
	}
	while (i < mid) {
		b.push_back(a[i++]);
	}
	while (j < R) {
		ans += mid - i;
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
	cin >> n >> m >> a0 >> b0;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i)
		a[i] = (ll)nextRand24() % m;
	merge_sort(a, 0, n);
	cout << ans;
	return 0;
}
