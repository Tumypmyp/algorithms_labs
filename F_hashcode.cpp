#include <bits/stdc++.h>

#pragma GCC optimize("O3")

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int H = 2e6, BIG = 1e9 + 7, MOD = 9369319, P = 31;


int bad_hash(string s) {
	int p = 1;
	int h = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		h += s[(int)s.size() - 1 - i] * p;
		p *= P;
	}
	return h;
}

map<int, vector<string>> ans;

void rec(vector<char> &a) {
	if (a.size() > 5)
		return;
	for (char ch = 'a'; ch <= 'c'; ++ch) {
		a.push_back(ch);
		rec(a);
		a.pop_back();
	}
	for (char ch = 'A'; ch <= 'C'; ++ch) {
		a.push_back(ch);
		rec(a);
		a.pop_back();
	}
	string s(a.begin(), a.end());

	// cout << s << endl;
	ans[bad_hash(s)].push_back(s);
}

const vector<string> B{"Aaaaa", "AaabB", "AabBa", "AabCB", "AbBaa", "AbBbB", "AbCBa", "AbCCB",
	"BBaaa", "BBabB", "BBbBa", "BBbCB", "BCBaa", "BCBbB", "BCCBa", "BCCCB"};

const int K = (int)B.size();

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("map.in", "r", stdin), freopen("map.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int ind = i;
		for (int j = 0; j < 4; ++j) {
			cout << B[ind % K];
			ind /= K;
		}
		cout << "\n";
	}

	return 0;

	cout << bad_hash("AaaaaAaaaaAaaaaAaaaa") << "\n";
	cout << bad_hash("AaabBAaaaaAaaaaAaaaa") << "\n";
	vector<char> a;
	rec(a);
	int max_sz = 0;
	int max_h = 0;
	for (auto p : ans) {
		// cout << p.first << " " << p.second.size() << "\n";
		if ((int)p.second.size() > max_sz) {
			max_sz = (int)p.second.size();
			max_h = p.first;
		}
	}
	cout << max_h << " " << max_sz << "\n";
	for (auto p : ans[max_h]) {
		cout << p << "\", \"";
	}

	return 0;
}
