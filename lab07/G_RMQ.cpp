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
	ll val = 0, set = 0, add = 0;
	bool set_b = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2) {
		L = L2;
		R = R2;
	}
};

void upd(Node* v) {
	if (!v)
		return;
	if (v->set_b) {
		v->set_b = 0;
		v->val = v->set;
		if (v->left) {
			v->left->set = v->set;
			v->right->set = v->set;
			v->left->set_b = 1;
			v->right->set_b = 1;
			v->left->add = 0;
			v->right->add = 0;
		}
	}
	v->val += v->add;
	if (v->left) {
		v->left->add += v->add;
		v->right->add += v->add;
	}
	v->add = 0;
}


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


void add_x(Node* v, int L, int R, ll x) {
	upd(v);
	if (v->R <= L || R <= v->L)
		return;
	if (L <= v->L && v->R <= R) {
		v->add += x;
		return;
	}
	add_x(v->left, L, R, x);
	add_x(v->right, L, R, x);
	upd(v), upd(v->left), upd(v->right);
	v->val = min(v->left->val, v->right->val);
}

void set_x(Node* v, int L, int R, ll x) {
	upd(v);
	if (v->R <= L || R <= v->L)
		return;
	// cout << v->L << "|" << v->R << " " << L << "|" << R << "\n";
	if (L <= v->L && v->R <= R) {
		v->set_b = true;
		v->set = x;
		// cout << x << "!!\n";
		upd(v);
		return;
	}
	set_x(v->left, L, R, x);
	set_x(v->right, L, R, x);
	upd(v), upd(v->left), upd(v->right);
	v->val = min(v->left->val, v->right->val);
}

ll get_min(Node* v, int L, int R) {
	upd(v);
	if (v->R <= L || R <= v->L)
		return BIG;
	if (L <= v->L && v->R <= R) {
		// cout << v->L << " " << v->R << "-" << v->val << ", ";
		return v->val;
	}
	return min(get_min(v->left, L, R), get_min(v->right, L, R));
}

void out_tree(Node* v) {
	if (!v)
		return;
	if (!v->left) {
		cout << "[" << v->val << "," << v->add << "," << v->set * v->set_b << "]";
		return;
	}
	cout << "(";
	out_tree(v->left);
	cout << ")" << v->val << "," << v->add << "," << v->set * v->set_b << "(";
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
	int n;
	ll a;
	cin >> n;
	Node* tree = build(1, n + 1);

	for (int i = 1; i <= n; ++i) {
		cin >> a;
		set_x(tree, i, i + 1, a);
	}
	// out_tree(tree);
	// cout << "\n";
	string s;
	int x, y;
	ll z;
	while (cin >> s >> x >> y) {
		if (s == "min") {
			cout << get_min(tree, x, y + 1) << "\n";
		} else  {
			cin >> z;
			if (s == "set")
				set_x(tree, x, y + 1, z);
			else
				add_x(tree, x, y + 1, z);
			// out_tree(tree);
			// cout << "\n";
		}
	}
	return 0;
}
