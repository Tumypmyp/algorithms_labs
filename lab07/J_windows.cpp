#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9, MAX_X = 1e6;

struct segment{
	int x, y1, y2, add;
};


struct Node{
	int L, R;
	int set = 0, add = 0;
	point val;
	bool set_b = 0;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2) {
		val.y = L2;
		L = L2;
		R = R2;
	}
};

void upd(Node* v) {
	if (!v)
		return;
	if (v->set_b) {
		v->set_b = 0;
		v->val.x = v->set;
		if (v->left) {
			v->left->set = v->set;
			v->right->set = v->set;
			v->left->set_b = 1;
			v->right->set_b = 1;
			v->left->add = 0;
			v->right->add = 0;
		}
	}
	v->val.x += v->add;
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


void add_x(Node* v, int L, int R, int x) {
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
	v->val = max(v->left->val, v->right->val);
}

void set_x(Node* v, int L, int R, int x) {
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
	v->val = max(v->left->val, v->right->val);
}

Node* get_max(Node* v, int L, int R) {
	upd(v);
	if (v->R <= L || R <= v->L)
		return nullptr;
	if (L <= v->L && v->R <= R) {
		// cout << v->L << " " << v->R << "-" << v->val << ", ";
		return v;
	}
	auto v1 = get_max(v->left, L, R);
	auto v2 = get_max(v->right, L, R);
	if (!v1)
		return v2;
	if (!v2)
		return v1;
	if (v2->val < v1->val)
		return v1;
	return v2;
}

void out_tree(Node* v) {
	if (!v)
		return;
	if (!v->left) {
		cout << "[" << v->val.x << "," << v->add << "," << v->set * v->set_b << "]";
		return;
	}
	cout << "(";
	out_tree(v->left);
	cout << ")" << v->val.x << "," << v->add << "," << v->set * v->set_b << "(";
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
	cin >> n;
	point a, b;
	vector<segment> sc;
	for (int i = 1; i <= n; ++i) {
		cin >> a.x >> a.y >> b.x >> b.y;
		sc.push_back({a.x, a.y, b.y, 1});
		sc.push_back({b.x, a.y, b.y, -1});
	}
	sort(sc.begin(), sc.end(), [](segment &p1, segment &p2) {
		return mp(p1.x, p2.add) < mp(p2.x, p1.add);
	});
	Node* tree = build(-MAX_X, MAX_X + 1);
	point ans;
	int ans_val = 0;
	for (auto &s : sc) {
		add_x(tree, s.y1, s.y2 + 1, s.add);
		auto p = get_max(tree, -MAX_X, MAX_X + 1);
		if (p->val.x > ans_val) {
			ans_val = p->val.x;
			ans = {s.x, p->val.y};
		}
		// cout << s.x << " " << s.y1 << " " << s.y2 << " " << s.add << "\n";
		// cout << p->val.x << " <-" << s.x << " " << p->val.y << " ";
		// out_tree(tree);
		// cout << "\n\n";
	}
	cout << ans_val << "\n" << ans.x << " " << ans.y;

	return 0;
}
