#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll BIG = 1e10;

ll sz = 0;

vector<pair<ll, ll>> a(1);
vector<ll> ind(1), place(1);


void out() {
	cout << sz << "\n";
	for (auto &p : a)
		cout << p.first << " " << p.second << " ";
	cout << "\n";
	for (auto &p : ind)
		cout << p << " ";
	cout << "\n";
	for (auto &p : place)
		cout << p << " ";
	cout << "\n\n";
	//*/
}

void big_swap(ll x, ll y) {
	swap(a[x], a[y]);
	swap(ind[x], ind[y]);
	swap(place[ind[x]], place[ind[y]]);
}

void refresh_up(ll x) {
	// out();
	while (x > 1) {
		if (a[x] < a[x / 2]) {
			big_swap(x, x / 2);
			x /= 2;
		} else {
			break;
		}
		// out();
	}
}

void refresh_down(ll x) {
	while (x * 2 <= sz) {
		if (x * 2 + 1 <= sz) {
			ll y = x * 2;
			if (a[y] > a[y + 1])
				y++;
			if (a[y] < a[x]) {
				big_swap(y, x);
				x = y;
			} else {
				break;
			}
		} else {
			if (a[x * 2] < a[x]) {
				big_swap(x * 2, x);
				x *= 2;
			} else {
				break;
			}
		}
	}
}

void push(pair<ll, ll> x) {
	sz++;
	ind.push_back((ll)place.size());
	place.push_back(sz);
	a.push_back(x);
	refresh_up(sz);
}

pair<ll, ll> get_min() {
	if (sz == 0) {
		return {BIG, BIG};
	}
	auto ans = a[1];
	big_swap(1, sz);
	place[ind[sz]] = 0;
	a.pop_back();
	ind.pop_back();
	sz--;
	// out();
	if (sz > 0)
		refresh_down(1);
	return ans;
}

void decrease(ll x, pair<ll, ll> y) {
	a[place[x]] = y;
	refresh_up(place[x]);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	ll n, m;
	cin >> n >> m;
	vector<ll> ans(n, 1e10);
	vector<pair<pair<int, int>, int>> q;
	int x, y, val;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y >> val;
		q.push_back({{x, i}, val});
		q.push_back({{y, -i}, val});
	}
	sort(q.begin(), q.end());
	int j = 0;
	for (int i = 0; i < n; ++i) {
		while (j < q.size() && q[j].first.first <= i) {
			if (push({q[j].second, q[j].first.second});
			++j;
		}
	}
	return 0;
	
}
