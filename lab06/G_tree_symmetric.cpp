#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const ll H = 2e6, BIG = 1e9 + 7, MOD = 9369319, P = 29, MOD2 = 32416190071, P2 = 31;

int n, max_v, max_len, base = -1;
vector<int> d, v1, par;
vector<ll> pows, pows2;
vector<vector<int>> gr;

void dfs(int v, int parent = -1) {
	int max_v1 = -1, max_v2 = -1, max_v1_d = 0, max_v2_d = 0;
	par[v] = parent;
	for (auto &p : gr[v]) {
		if (p == parent)
			continue;
		dfs(p, v);
		if (d[p] > max_v1_d) {
			swap(max_v2_d, max_v1_d);
			swap(max_v2, max_v1);
			max_v1 = p;
			max_v1_d = d[p];
		} else if (d[p] > max_v2_d) {
			max_v2 = p;
			max_v2_d = d[p];
		}
	}
	if (max_v2_d + max_v1_d + 1 > max_len) {
		max_len = max_v2_d + max_v1_d + 1;
		max_v = v;
	}
	v1[v] = max_v1;
	d[v] = max_v1_d + 1;
}

struct Node{
	ll size, hash, hash2, sum;
	vector<Node*> sons;
	Node(vector<Node*> &a){
		sons = a;
		sort(sons.begin(), sons.end(), [](Node* p1, Node* p2) {
			return vector<ll>{p1->size, p1->hash, p1->hash2}
						< vector<ll>{p2->size, p2->hash, p2->hash2};
		});
		size = (ll)sons.size();
		hash = 0;
		sum = 1;
		for (ll i = 0; i < size; ++i) {
			hash += sons[i]->hash * pows[i];
			hash %= MOD;
			sum += sons[i]->sum;
		}
		hash2 = sum;
		for (ll i = 0; i < size; ++i) {
			hash2 += sons[i]->hash2 * pows2[i] + sons[i]->size;
			hash2 %= MOD2;
		}
	}
};


Node* dfs2(int v, int parent = -1) {
	vector<Node*> ans;
	par[v] = parent;
	for (auto &p : gr[v]) {
		if (p == parent || p == base)
			continue;
		ans.push_back(dfs2(p, v));
	}
	return new Node(ans);
}


bool equals(Node* v1, Node* v2) {
	return v1->sum == v2->sum && v1->hash == v2->hash && v1->hash2 == v2->hash2;
}

void out_tree(Node* v) {
	cout << v->size << ": {";
	for (auto &p : v->sons) {
		out_tree(p);
	}
	cout << "} = " << v->hash << "\n";
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("linkedmap.in", "r", stdin), freopen("linkedmap.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	pows.resize(1e5 + 3, 1);
	for (int i = 1; i < (int)pows.size(); ++i) {
		pows[i] = pows[i - 1] * P;
		pows[i] %= MOD;
	}
	pows2.resize(1e5 + 3, 1);
	for (int i = 1; i < (int)pows2.size(); ++i) {
		pows2[i] = pows[i - 1] * P2 + 7;
		pows2[i] %= MOD2;
	}

	int fr, to;
	cin >> n;
	if (n == 1) {
		cout << "NO";
		return 0;
	}
	gr.resize(n);
	for (int i = 0; i < n - 1; ++i) {
		cin >> fr >> to, --fr, --to;
		gr[fr].push_back(to);
		gr[to].push_back(fr);
	}
	d.resize(n, 1);
	v1.resize(n, -1);
	par.resize(n);
	// find longest way
	dfs(0);
	if (max_len % 2 == 0) {
		cout << "NO";
		return 0;
	}
	// find center
	int ans_v1, ans_v2;
	if (d[v1[max_v]] * 2 + 1 == max_len) {
		if (max_v == 0) {
			if (gr[0].size() != 2) {
				cout << "NO";
				return 0;
			}
			base = 0;
			ans_v1 = gr[0][0];
			ans_v2 = gr[0][1];
		} else {
			cout << "NO";
			return 0;
		}
	} else {
		// cout << "not center first" << endl;
		int v = max_v;
		for (int i = 0; i < d[v1[max_v]] - max_len / 2; ++i) {
			v = v1[v];
			if (v == -1) {
				cout << "NO";
				return 0;
			}
		}
		// cout << "new base is " << v << endl;
		if (gr[v].size() != 2) {
			cout << "NO";
			return 0;
		}
		base = v;
		ans_v1 = gr[v][0];
		ans_v2 = gr[v][1];
	}
	Node* ans1 = dfs2(ans_v1);
	Node* ans2 = dfs2(ans_v2);
	// out_tree(ans1);
	// out_tree(ans2);
	cout << (equals(ans1, ans2) ? "YES" : "NO");

	return 0;
}
