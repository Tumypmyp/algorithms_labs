#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 5e3, BIG = 1e9 + 7, MOD = 1e9;

mt19937 gen(123);

int get_rand(int L, int R) {
	return abs((int)gen()) % (R - L) + L;
}

struct Node{
	int val, prior, ind, size;
	Node* L;
	Node* R;
	Node(int v, int i) {
		size = 1;
		val = v;
		prior = get_rand(0, 1e9);
		ind = i;
		L = nullptr;
		R = nullptr;
	}
};

int get_ind(Node* v) {
	return v ? v->ind : 0;
}

int get_size(Node* v) {
	return v ? v->size : 0;
}

void upd(Node* v) {
	if (!v)
		return;
	v->size = get_size(v->L) + get_size(v->R) + 1;
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

Node* find(Node* v, int x) {
	if (!v || v->val == x)
		return v;
	if (x < v->val)
		return find(v->L, x);
	else
		return find(v->R, x);
}

Node* get_v(Node* v, int k) {
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

pair<Node*, Node*> split(Node* v, int k) {
	if (!v)
		return {nullptr, nullptr};
	if (get_size(v->L) >= k) {
		auto p = split(v->L, k);
		v->L = p.y;
		upd(v);
		return {p.x, v};
	} else {
		auto p = split(v->R, k - get_size(v->L) - 1);
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

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	Node* tree = nullptr;
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		tree = merge(tree, new Node(i, i));
		// out_tree(tree); cout << endl;
	}
	int L, R;
	for (int i = 0; i < m; ++i) {
		cin >> L >> R;
		// cout << L << " " << R << endl;
		auto p = split(tree, R);
		auto p2 = split(p.x, L - 1);
		tree = merge(p2.y, merge(p2.x, p.y));
	}
	for (int i = 0; i < n; ++i)
		cout << get_ind(get_v(tree, i + 1)) << " ";
	return 0;
}
