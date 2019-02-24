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

pair<Node*, Node*> split(Node* v, int x) {
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

pair<Node*, Node*> split_k(Node* v, int k) {
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
	auto p = split(root, v->val);
	return merge(p.x, merge(v, p.y));
}

Node* erase(Node* root, int x) {
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
	int n, t, x;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> t >> x;
		if (t == 1) {
			tree = insert(tree, new Node(x, i));
		} else if (t == -1) {
			tree = erase(tree, x);
		} else {
			cout << get_v(tree, get_size(tree) - x + 1)->val << "\n";
		}
		// out_tree2(tree, "\n");
	}
	return 0;
}
