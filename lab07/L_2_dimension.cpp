#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9;

struct Node{
	vector<int> val;
	int L, R;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2) {
		L = L2;
		R = R2;
	}
};

Node* build(int L, int R, vector<int> &a) {
	Node* v = new Node(L, R);
	if (L + 1 == R) {
		v->val.push_back(a[L]);
		return v;
	}
	int mid = (L + R) / 2;
	v->left = build(L, mid, a);
	v->right = build(mid, R, a);
	v->val.resize(v->left->val.size() + v->right->val.size());
	merge(v->left->val.begin(), v->left->val.end(),
		v->right->val.begin(), v->right->val.end(), v->val.begin());
	return v;
}

int get_num(Node* v, int L, int R, int x, int y) {
	if (v->R <= L || R <= v->L)
		return 0;
	if (L <= v->L && v->R <= R) {
		auto R = upper_bound(v->val.begin(), v->val.end(), y);
		auto L = lower_bound(v->val.begin(), v->val.end(), x);
		return int(R - L);
	}
	return get_num(v->left, L, R, x, y) + get_num(v->right, L, R, x, y);
}

unsigned int a, b;
unsigned int cur = 0;
unsigned int nextRand17() {
	cur = cur * a + b;
	return cur >> 15;
}
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	/*/
	int n, q, L, R, x, y;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];

	Node* tree = build(0, n, a);
	cin >> q;
	for (int i = 0; i < q; ++i) {
		cin >> L >> R >> x >> y, ++R;
		cout << get_num(tree, L, R, x, y) << "\n";
	}
	/*/
	int q, n = 1 << 17;
	cin >> q >> a >> b;

	vector<int> f(n);
	for (int i = 0; i < n; i++)
		f[i] = nextRand24();

	Node* tree = build(0, n, f);

	unsigned int sum = 0;
	for (int i = 0; i < q; ++i) {
		int l = nextRand17();
		int r = nextRand17();
		if (l > r) swap(l, r);
		++r;
		int x = nextRand24();
		int y = nextRand24();
		if (x > y) swap(x, y);
		int ans = get_num(tree, l, r, x, y);
		sum += ans;
		b += ans;
	}
	cout << sum;

	//*/
	return 0;
}
