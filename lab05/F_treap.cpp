#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define poll pair<ll, ll>
#define mp make_pair

const ll N = 5e3, BIG = 1e9 + 7, MOD = 1e9;

mt19937 gen(123);

ll get_rand(ll L, ll R) {
	return abs((ll)gen()) % (R - L) + L;
}

struct Node{
	ll val, prior, ind, size;
	bool zero;
	Node* L;
	Node* R;
	Node(ll v, ll i) {
		zero = (v == 0);
		size = 1;
		val = v;
		prior = get_rand(0, 1e9);
		ind = i;
		L = nullptr;
		R = nullptr;
	}
};

ll get_ind(Node* v) {
	return v ? v->ind : 0;
}

ll get_size(Node* v) {
	return v ? v->size : 0;
}


bool get_zero(Node* v) {
	return v ? v->zero : 0;
}


void out_val(Node* v, string end = "") {
	if (v)
		cout << "[" << v->val << "|" << v->size << "|" << (ll)v->zero << "]";
	else
		cout << "none";
	cout << end;
	cout.flush();
}


void upd(Node* v) {
	if (!v)
		return;
	v->size = get_size(v->L) + get_size(v->R) + 1;
	v->zero = get_zero(v->L) || get_zero(v->R) || v == 0;
}

void out_tree(Node* v) {
	if (!v)
		return;
	cout << "(";
	out_tree(v->L);
	cout << ")";
	out_val(v);
	cout << "(";
	out_tree(v->R);
	cout << ")";
}

void out_tree2(Node* v, string end = "") {
	out_tree(v);
	cout << end;
	cout.flush();
}

Node* find(Node* v, ll x) {
	if (!v || v->val == x)
		return v;
	if (x < v->val)
		return find(v->L, x);
	else
		return find(v->R, x);
}

Node* get_v(Node* v, ll k) {
	if (!v)
		return nullptr;
	if (get_size(v->L) >= k) {
		return get_v(v->L, k);
	} else if (get_size(v->L) + 1 == k) {
		return v;
	} else {
		return get_v(v->R, k - get_size(v->L) - 1);
	}
}

pair<Node*, Node*> split(Node* v, ll x) {
	if (!v)
		return {nullptr, nullptr};
	if (x <= v->val) {
		auto p = split(v->L, x);
		v->L = p.y;
		upd(v);
		return {p.x, v};
	} else {
		auto p = split(v->R, x);
		v->R = p.x;
		upd(v);
		return {v, p.y};
	}
}

pair<Node*, Node*> split_k(Node* v, ll k) {
	if (!v)
		return {nullptr, nullptr};
	if (get_size(v->L) >= k) {
		auto p = split_k(v->L, k);
		v->L = p.y;
		upd(v);
		return {p.x, v};
	} else {
		auto p = split_k(v->R, k - get_size(v->L) - 1);
		v->R = p.x;
		upd(v);
		return {v, p.y};
	}
}

pair<Node*, Node*> split_zero(Node* v) {
	if (!v)
		return {nullptr, nullptr};
	if (get_zero(v->L) || v->val == 0) {
		auto p = split_zero(v->L);
		v->L = p.y;
		upd(v);
		return {p.x, v};
	} else {
		auto p = split_zero(v->R);
		v->R = p.x;
		upd(v);
		return {v, p.y};
	}
}

Node* merge(Node* v1, Node* v2) {
	if (!v1)
		return v2;
	if (!v2)
		return v1;
	if (v1->prior < v2->prior) {
		v1->R = merge(v1->R, v2);
		upd(v1);
		return v1;
	} else {
		v2->L = merge(v1, v2->L);
		upd(v2);
		return v2;
	}
}


Node* insert(Node* root, Node* v) {
	if (find(root, v->val))
		return root;
	auto p = split(root, v->val);
	return merge(p.x, merge(v, p.y));
}

Node* erase(Node* root, ll x) {
	auto p = split(root, x);
	auto p2 = split(p.y, x + 1);
	delete p2.x;
	return merge(p.x, p2.y);
}

Node* erase_k(Node* root, ll k) {
	auto p = split_k(root, k - 1);
	auto p2 = split_k(p.y, 1);
	// out_tree2(p.x, "p.x erase\n");
	// out_tree2(p2.x, "p2.x erase\n");
	// out_tree2(p2.y, "p2.y erase\n");
	delete p2.x;
	return merge(p.x, p2.y);
}

//not accepted
int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	Node* tree = nullptr;

	ll n, m, x;
	cin >> n >> m;
	for (ll i = 0; i < m; ++i) {
		tree = merge(tree, new Node(0, i));
		// out_tree2(tree, "\n");
	}

	for (ll i = 1; i <= n; ++i) {
		cin >> x;
		auto p = split_k(tree, x - 1);
		// out_tree2(p.y, "- to split by zero\n");
		auto p2 = split_zero(p.y);
		// out_tree2(p2.x, "-zero_x\n");
		// out_tree2(p2.y, "-zero_y\n");
		auto p3 = erase_k(p2.y, 1);
		// out_tree2(p3, "-zero_y_del_1\n");
		tree = merge(p.x, merge(new Node(i, -i), merge(p2.x, p3)));
		// out_tree2(tree, "\n\n");
	}
	// out_tree2(tree, "end\n");
	while (get_size(tree) > 0 && get_v(tree, get_size(tree))->val == 0) {
		tree = erase_k(tree, get_size(tree));
		// out_tree2(tree, "end\n");
	}
	cout << get_size(tree) << "\n";
	for (ll i = 0; i < get_size(tree); ++i)
		cout << get_v(tree, i + 1)->val << " ";
	return 0;
}
