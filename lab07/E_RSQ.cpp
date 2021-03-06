#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9;

struct Node{
	int L, R;
	ll val = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2) {
		L = L2;
		R = R2;
	}
};

Node* build(int L, int R) {
	Node* v = new Node(L, R);
	if (L + 1 == R) {
		return v;
	}
	int mid = (L + R) / 2;
	v->left = build(L, mid);
	v->right = build(mid, R);
	return v;
}

void set_x(Node* v, int i, ll x) {
	if (v->R <= i || i < v->L)
		return;
	if (v->L + 1 == v->R) {
		v->val = x;
		return;
	}
	set_x(v->left, i, x);
	set_x(v->right, i, x);
	v->val = v->left->val + v->right->val;
}

ll get_sum(Node* v, int L, int R) {
	if (v->R <= L || R <= v->L)
		return 0;
	if (L <= v->L && v->R <= R) {
		// cout << v->L << " " << v->R << "-" << v->val << ", ";
		return v->val;
	}
	return get_sum(v->left, L, R) + get_sum(v->right, L, R);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, a;
	cin >> n;
	Node* tree = build(1, n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> a;
		set_x(tree, i, a);
	}
	string s;
	int x, y;
	while (cin >> s >> x >> y) {
		if (s == "sum")
			cout << get_sum(tree, x, y + 1) << "\n";
		else
			set_x(tree, x, y);
	}
	return 0;
}
