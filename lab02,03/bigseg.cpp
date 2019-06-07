#include <bits/stdc++.h>

using namespace std;

typedef long long ll;



const int MAXN = 1 << 16;


ll n, k, ans;

unsigned int cur = 0, a, b;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

unsigned int nextRand32() {
	unsigned int a1 = nextRand24();
	unsigned int b1 = nextRand24();
	return (a1 << 8) ^ b1;
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> n >> k >> a >> b;
	vector<ll> c(n);
	for (int i = 0; i < n; ++i) {
		c[i] = (int)nextRand32();
		// cout << c[i] << " ";
	}
	ll sum = 0;
	for (int L = 0, R = 0; L < n;) {
		while (R < n && sum < k) {
			sum += c[R++];
		}
		cout << L << " " << R << " + " << n - R + ll(sum >= k) << "\n";
		ans += n - R + ll(sum >= k);
		sum -= c[L++];
	}
	cout << ans;

	return 0;
}
