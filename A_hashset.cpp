#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int H = 2e6, BIG = 1e9 + 7, MOD = 1e9;

int myhash(int x) {
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = ((x >> 16) ^ x) * 0x45d9f3b;
	x = (x >> 16) ^ x;
	return x % H;
}

vector<int> a[H];


bool exists(int v) {
	for (auto &p : a[myhash(v)])
		if (p == v)
			return true;
	return false;
}

void insert(int v) {
	if (!exists(v))
		a[myhash(v)].push_back(v);
}

void erase(int v) {
	auto &p = a[myhash(v)];
	for (int i = 0; i < (int)p.size(); ++i)
		if (p[i] == v) {
			p.erase(p.begin() + i);
			return;
		}
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string t;
	int x;
	while (cin >> t >> x) {
		if (t[0] == 'i')
			insert(x);
		else if (t[0] == 'd')
			erase(x);
		else
			cout << (exists(x) ? "true\n" : "false\n");
	}
	return 0;
}
