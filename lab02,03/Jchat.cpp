#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Node{
	ll v, read, sz, par;
};

vector<Node> a;

ll get_sum(ll x) {
	if (a[x].par == x)
		return a[x].v;
	return a[x].v + get_sum(a[x].par);
}

ll get(ll x) {
	if (a[x].par == x)
		return x;
	return get(a[x].par);
}

void merge(ll x, ll y) {
	x = get(x);
	y = get(y);
	if (a[x].sz > a[y].sz)
		swap(x, y);
	a[x].par = y;
	a[y].sz += a[x].sz;
	a[x].v -= a[y].v;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n, m, p = 1e6 + 3;
	cin >> n >> m;
	a.resize(n);
	for (ll i = 0; i < n; ++i)
		a[i] = {0, 0, 1, i};

	ll t, zerg = 0, x, y;
	for (ll i = 0; i < m; ++i) {
		// cout << zerg << "-z\n";
		cin >> t >> x;
		x = (x + zerg) % n;
		// cout << x << " - x\n";
		if (t == 1) {
			a[get(x)].v++;
			zerg = (30 * zerg + 239) % p;
		} else if (t == 2) {
			cin >> y;
			y = (y + zerg) % n;
			if (get(x) != get(y)) {
				merge(x, y);
				zerg = (13 * zerg + 11) % p;
			}
		} else {
			ll q = get_sum(x) - a[x].read;
			cout << q << "\n";
			a[x].read += q;
			zerg = (100500 * zerg + q) % p;
		}

		/*/
		for (ll i = 0; i < n; ++i) {
			auto p = a[i];
			cout << get_sum(i) - a[i].read << " " << p.v << " " << p.sz << " " << p.par << "\n";
		}
		cout << "\n";
		//*/
	}

	return 0;
}
