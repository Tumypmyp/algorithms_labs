#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<ll, ll>
#define mp make_pair


const ll N = 1103, N2 = N / 9, BIG = 2e9 + 7, MOD = 999999937;


bool getb(ll a, ll ind) {
	return (a >> ind) & 1;
}

ll invb(ll a, ll ind) {
	return a ^ (1 << ind);
}

ll get_num(ll a, ll n) {
	ll ans = 0;
	for (ll i = 0; i < n; ++i)
		ans += getb(a, i);
	return ans;
}

void out_mask(ll a, ll n, string s = " ") {
	for (ll i = 0; i < n; ++i)
		cout << getb(a, i);
	cout << s;
}



ll mod;

struct matrix{
	vector<vector<ll>> a;
	matrix(ll n = 0, ll m = 0) {
		a.resize(n, vector<ll> (m));
	}
};

matrix one(ll n) {
	matrix ans = matrix(n, n);
	for (ll i = 0; i < n; ++i)
		ans.a[i][i] = 1;
	return ans;
}


matrix gen_dp(ll n) {
	matrix ans;
	ans.a.resize(1 << n, vector<ll> (1 << n, 1));
	for (ll mask1 = 0; mask1 < (1 << n); ++mask1)
		for (ll mask2 = 0; mask2 < (1 << n); ++mask2)
			for (ll i = 0; i < (n - 1); ++i) {
				if (getb(mask1, i) && getb(mask1, i + 1)
						&& getb(mask2, i) && getb(mask2, i + 1))
					ans.a[mask1][mask2] = 0;
				if (!getb(mask1, i) && !getb(mask1, i + 1)
						&& !getb(mask2, i) && !getb(mask2, i + 1))
					ans.a[mask1][mask2] = 0;
			}
	return ans;
}


void out_matrix(matrix a) {
	for (auto &v : a.a) {
		for (auto &p : v)
			cout << p << " ";
		cout << "\n";
	}
	cout << endl;
}

matrix mult(matrix a, matrix b) {
	// out(a);
	// out(b);
	// cout << "\nnow mult\n";
	matrix ans = matrix((ll)a.a.size(), (ll)b.a[0].size());
	for (ll i = 0; i < (ll)ans.a.size(); ++i)
		for (ll j = 0; j < (ll)ans.a[i].size(); ++j) {
			for (ll u = 0; u < (ll)b.a.size(); ++u) {
				ans.a[i][j] += a.a[i][u] * b.a[u][j];
				ans.a[i][j] %= mod;
			}
			// out(ans);
		}
	return ans;
}

vector<ll> div2(vector<ll> x) {
	for (ll i = (ll)x.size() - 1; i >= 0; --i) {
		if (i > 0 && x[i] % 2 != 0)
			x[i - 1] += 10;
		x[i] /= 2;
	}
	while (!x.empty() && x.back() == 0) {
		x.pop_back();
	}
	return x;
}

matrix pow(matrix a, vector<ll> x) {
	// for (auto &p : x)
	// 	cout << p;
	// cout << " x" << endl;
	if (x.empty())
		return one((ll)a.a.size());
	auto sq = pow(a, div2(x));
	sq = mult(sq, sq);
	if (x[0] % 2 != 0)
		sq = mult(sq, a);
	return sq;
}



int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("nice3.in", "r", stdin), freopen("nice3.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	ll m;
	cin >> s >> m >> mod;
	// out_matrix(gen_dp(m));
	// reading
	vector<ll> x(s.size());
	for (ll i = 0; i < (ll)s.size(); ++i)
		x[i] = s[(ll)s.size() - 1 - i] - '0';
	// minus1

	ll j = 0;
	while (j < (ll)x.size() && x[j] == 0) {
		x[j] = 9;
		++j;
	}
	x[j]--;
	while (!x.empty() && x.back() == 0) {
		x.pop_back();
	}

	// for (auto &p : x)
	// 	cout << p;
	// cout << endl;

	matrix beg;
	beg.a.resize(1 << m, vector<ll> (1, 1));
	matrix ans = mult(pow(gen_dp(m), x), beg);
	// out_matrix(ans);
	// cout << " - ans\n";
	ll sum = 0;
	for (auto &v : ans.a)
		for (auto &p : v) {
			sum += p;
			sum %= mod;
		}
	cout << sum;
	return 0;
}
