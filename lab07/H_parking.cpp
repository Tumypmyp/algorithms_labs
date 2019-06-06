#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll n = 1 << 24, BIG = 1e18 + 7, MOD = 1e9;


struct Node{
	int L, R;
	int max_ind;
	bool val = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2) {
		L = L2;
		R = R2;
		max_ind = R2 - 1;
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


void set_x(Node* v, int L, bool x) {
	if (v->R <= L || L + 1 <= v->L)
		return;
	if (L <= v->L && v->R <= L + 1) {
		v->val = x;
		v->max_ind = x ? 0 : L;
		return;
	}
	set_x(v->left, L, x);
	set_x(v->right, L, x);
	v->val = v->left->val || v->right->val;
	v->max_ind = max(v->left->max_ind, v->right->max_ind);
}

Node* get_first(Node* v, int L) {
	if (v->L + 1 == v->R)
		return v;
	if (v->left->max_ind >= L)
		return get_first(v->left, L);
	else if (v->right->max_ind != 0)
		return get_first(v->right, L);
	else
		return nullptr;
}


void out_tree(Node* v) {
	if (!v)
		return;
	if (!v->left) {
		cout << "[" << v->val << "," << v->max_ind << "]";
		return;
	}
	cout << "(";
	out_tree(v->left);
	cout << ")" << v->val << "(";
	out_tree(v->right);
	cout << ")";
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >>  m;
	Node* tree = build(1, n + 1);
	int x;
	string t;
	for (int i = 0; i < m; ++i) {
		cin >> t >> x;
		if (t == "exit") {
			set_x(tree, x, 0);
		} else  {
			Node* ans = get_first(tree, x);
			if (!ans)
				ans = get_first(tree, 1);
			cout << ans->L << "\n";
			set_x(tree, ans->L, 1);
		}
		// out_tree(tree);
		// cout << "\n\n";
	}
	return 0;
}
