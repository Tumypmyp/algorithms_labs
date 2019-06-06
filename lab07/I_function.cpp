#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e6 + 7, MOD = 1e9;


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<ll> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];

	vector<pair<point, int>> v(m);
	for (int i = 0; i < m; ++i)
		cin >> v[i].x.x >> v[i].x.y, --v[i].x.x, v[i].y = i;

	int K = 1000;
	sort(v.begin(), v.end(), [K](pair<point, int> &p1, pair<point, int> &p2) {
		if (p1.x.x / K != p2.x.x / K)
			return	p1.x.x / K < p2.x.x / K;
		return p1.x.y > p2.x.y;
	});
	vector<ll> ans(m), cnt(BIG);
	ll L = 0, R = 0, fun = 0;
	for (auto &p : v) {
		point q = p.x;
		while (q.x < L) {
			--L;
			fun += (cnt[a[L]]++ * 2 + 1) * a[L];
		}
		while (q.y > R) {
			fun += (cnt[a[R]]++ * 2 + 1) * a[R];
			++R;
		}
		while (q.x > L) {
			fun -= (cnt[a[L]]-- * 2 - 1) * a[L];
			++L;
		}
		while (q.y < R) {
			--R;
			fun -= (cnt[a[R]]-- * 2 - 1) * a[R];
		}
		ans[p.y] = fun;
	}
	for (auto &p : ans)
		cout << p << "\n";

	return 0;
}
