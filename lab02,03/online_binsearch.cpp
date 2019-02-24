#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll x, m, a1;

ll norm(ll ind) {
	return (ind < 1 ? ind + (ll)1e18 - m : ind);
}

int main() {
	#ifdef ON_PC
		// freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> x >> m;
	cout << "? 1"  << endl;
	cin >> a1;
	ll R = x - a1 + 2;
	ll L = R - m - 1;
	ll a_mid;
	while (L + 1 < R) {
		// cout << L << " " << R << " [) \n";
		ll mid = (L + R) / 2;
		cout << "? " << norm(mid) << endl;
		cin >> a_mid;
		if (a_mid == x) {
			cout << "! " << norm(mid) << endl;
			return 0;
		}
		if (a_mid <= x || a_mid - 2 * m > x) {
			L = mid;
		} else {
			R = mid;
		}
	}
	// cout << L << " " << R << " [) " << endl;
	cout << "? " << norm(L) << endl;
	cin >> a_mid;
	if (a_mid == x) {
		cout << "! " << norm(L) << endl;
	} else {
		cout << "! -1" << endl;
	}
	return 0;
}
