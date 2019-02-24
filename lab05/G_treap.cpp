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
	ll val, prior, ind, size, sum;
	Node* L;
	Node* R;
	Node(ll v, ll i) {
		size = 1;
		val = v;
		sum = val;
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

ll get_sum(Node* v) {
	return v ? v->sum : 0;
}

void upd(Node* v) {
	if (!v)
		return;
	v->size = get_size(v->L) + get_size(v->R) + 1;
	v->sum = get_sum(v->L) + get_sum(v->R) + v->val;
}

void out_val(Node* v, string end = "") {
	if (v)
		cout << "[" << v->val << "|" << v->size << "]";
	else
		cout << "none";
	cout << end;
	cout.flush();
}

void out_tree(Node* v) {
	if (!v)
		return;
	cout << "(";
	out_tree(v->L);
	out_val(v);
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

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	Node* tree = nullptr;
	ll n, x, y, ans = 0;
	string t;
	cin >> n;
	for (ll i = 0; i < n; ++i) {
		cin >> t >> x;
		if (t == "+") {
			tree = insert(tree, new Node((x + ans) % (ll)1e9, i));
			// tree = insert(tree, new Node((x + ans) % (ll)1e9, i));
			ans = 0;
		} else {
			cin >> y;
			auto p = split(tree, x);
			auto p2 = split(p.y, y + 1);
			ans = get_sum(p2.x);
			tree = merge(p.x, merge(p2.x, p2.y));
			cout << ans << "\n";
		}

		// out_tree2(tree, "\n");
	}
	return 0;
}
