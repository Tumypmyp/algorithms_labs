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
	point val;
	Node* left = nullptr;
	Node* right = nullptr;
	Node(int L2, int R2, point v2) {
		L = L2;
		R = R2;
		val = v2;
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
	v->val = min(v->right->val, v->left->val);
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

int timer;
vector<vector<int>> gr;
vector<int> d, tin, tout;
vector<point> all;

void dfs(int v = 0, int d2 = 0) {
	tin[v] = timer++;
	d[v] = d2;
	all.push_back({d2, v});
	for (auto &to : gr[v]) {
		dfs(to, d2 + 1);
		all.push_back({d2, v});
	}
	tout[v] = timer++;
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
	int x, y;
	string s;
	vector<point> q;
	gr.resize(n);
	for (int i = 0; i < n; ++i) {
		cin >> s >> x >> y, --x, --y;
		if (s[0] == 'A')
			gr[x].push_back(y);
		else
			q.push_back({x, y});
	}
	d.resize(n);
	tin.resize(n);
	tout.resize(n);
	dfs();
	Node* tree = build(0, (int)all.size(), all);
	for (auto &p : q) {
		auto ans = get_min(tree, min(tin[p.x], tin[p.y]), max(tin[p.x], tin[p.y]) + 1);
		cout << ans.y + 1 << "\n";
	}

	return 0;
}
