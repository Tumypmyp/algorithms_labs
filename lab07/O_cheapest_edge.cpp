#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7, MOD = 1e9;

struct Node{
	point val;
	int L, R;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2, point v) {
		L = L2;
		R = R2;
		val = v;
	}
};

Node* build(int L, int R, vector<point> &a) {
	Node* v = new Node(L, R, a[L]);
	if (L + 1 == R) {
		return v;
	}
	int mid = (L + R) / 2;
	v->left = build(L, mid, a);
	v->right = build(mid, R, a);
	v->val = min(v->left->val, v->right->val);
	return v;
}

void set_x(Node* v, int i, point x) {
	if (v->R <= i || i < v->L)
		return;
	if (v->L + 1 == v->R) {
		v->val = x;
		return;
	}
	set_x(v->left, i, x);
	set_x(v->right, i, x);
	v->val = min(v->left->val, v->right->val);
}

point get_min(Node* v, int L, int R) {
	if (v->R <= L || R <= v->L)
		return {BIG, BIG};
	if (L <= v->L && v->R <= R) {
		return v->val;
	}
	return min(get_min(v->left, L, R), get_min(v->right, L, R));
}

vector<vector<point>> gr;
vector<point> par;
vector<int> d, sz, order, last, ind_in_way;
vector<bool> heavy;
vector<Node*> my_tree;

void dfs(int v = 0, int d2 = 0) {
	order.push_back(v);
	d[v] = d2;
	sz[v] = 1;
	for (auto &to : gr[v]) {
		dfs(to.x, d2 + 1);
		sz[v] += sz[to.x];
	}
	for (auto &to : gr[v]) {
		if (sz[to.x] * 2 >= sz[v])
			heavy[to.x] = 1;
	}
}

int get_ans(int v1, int v2) {
	// cout << v1 << " " << v2 << endl;
	if (v1 == v2) {
		return BIG;
	}
	if (last[v1] == last[v2]) {
		// cout << "==" << endl;
		if (d[v1] < d[v2])
			return get_ans(v2, v1);
		return get_min(my_tree[v1], ind_in_way[v1], ind_in_way[v2]).x;
	}
	if (d[last[v1]] < d[last[v2]])
		return get_ans(v2, v1);
	int pre_ans = get_min(my_tree[v1], ind_in_way[v1], my_tree[v1]->R).x;
	// cout << "min" << pre_ans << "\n";
	return min(get_ans(par[last[v1]].x, v2), pre_ans);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, x, y;
	cin >> n;
	gr.resize(n);
	par.resize(n);
	for (int i = 1; i < n; ++i) {
		cin >> x >> y, --x;
		gr[x].push_back({i, y});
		par[i] = {x, y};
	}
	d.resize(n);
	sz.resize(n);
	heavy.resize(n);
	dfs();
	heavy[0] = 1;
	/*/
	for (auto &v : gr) {
		for (auto &p : v)
			cout << p.x << " ";
		cout << endl;
	}
	for (auto &p : d)
		cout << p << " ";
	cout << "\n";
	for (auto &p : sz)
		cout << p << " ";
	cout << "\n";
	for (auto p : heavy)
		cout << p << " ";
	cout << endl;
	//*/
	my_tree.resize(n);
	last.resize(n);
	ind_in_way.resize(n);
	vector<bool> used(n);
	reverse(order.begin(), order.end());
	for (auto v : order) {
		if (used[v])
			continue;
		// cout << v << " : " << endl;
		auto v1 = v;
		vector<point> way;
		if (heavy[v]) {
			while (heavy[v]) {
				way.push_back({par[v].y, v});
				heavy[v] = 0;
				v = par[v].x;
			}
		} else {
			way.push_back({par[v].y, v});
			v = par[v].x;
		}
		// cout << "(";
		// for (auto &v2 : way)
		// 	cout << v2.y << " ";
		// cout << ")" << endl;
		// cout << v1 << " - ";
		my_tree[v1] = build(0, (int)way.size(), way);

		last[v1] = way.back().y;
		for (int i = 0; i < (int)way.size(); ++i) {
			auto v2 = way[i];
			used[v2.y] = true;
			// cout << v2.y << ", ";
			my_tree[v2.y] = my_tree[v1];
			last[v2.y] = last[v1];
			ind_in_way[v2.y] = i;
		}
		// cout << endl;
		// }
	}
	// for (auto &p : last)
	// 	cout << p << " ";
	// cout << "\n";


	int m;
	cin >> m;
	for (int i = 0; i < m; ++i) {
		cin >> x >> y, --x, --y;
		// cout << x << " " << y  << "{ " << endl;
		cout << get_ans(x, y) << "\n";
	}
	return 0;
}
