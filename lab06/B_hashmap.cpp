#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int H = 2e6, BIG = 1e9 + 7, MOD = 9369319, P = 29;

int myhash(string s) {
	int h = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		h *= P;
		h += s[i] - 'a' + 1;
		h %= MOD;
	}
	h = h % H + H;
	return h % H;
}

vector<pair<string, string>> a[H];



bool exists(string v) {
	for (auto &p : a[myhash(v)])
		if (p.x == v)
			return true;
	return false;
}

string get(string v) {
	for (auto &p : a[myhash(v)])
		if (p.x == v)
			return p.y;
	return "none";
}

void put(string v, string x) {
	if (!exists(v))
		a[myhash(v)].push_back({v, x});
	else
		for (auto &p : a[myhash(v)])
			if (p.x == v)
				p.y = x;
}

void erase(string v) {
	auto &p = a[myhash(v)];
	for (int i = 0; i < (int)p.size(); ++i)
		if (p[i].x == v) {
			p.erase(p.begin() + i);
			return;
		}
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("map.in", "r", stdin), freopen("map.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string t, x, y;
	while (cin >> t >> x) {
		if (t[0] == 'p') {
			cin >> y;
			put(x, y);
		} else if (t[0] == 'd') {
			erase(x);
		} else {
			cout << get(x) << "\n";
		}
	}
	return 0;
}
