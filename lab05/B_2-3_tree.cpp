#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 5e3, BIG = 1e9 + 7, MOD = 1e9;


// code is not complited 
struct Node{
	int val;
	vector<int> keys;
	vector<Node*> sons;
	Node* par;
	Node(int v = 0) {
		val = v;
		par = nullptr;
	}
};


void out_val(Node* v) {
	if (v)
		cout << v->val << "\n";
	else
		cout << "none\n";
}

void out_tree(Node* v) {
	if (!v)
		return;
	cout << "(";
	out_tree(v->L);
	cout << v->val;
	out_tree(v->R);
	cout << ")";
}

Node* find(Node* v, int x) {
	if (v->sons.empty())
		return v->val == v ? v : nullptr;
	if (v->sons.size() == 2) {
		if (v->keys[0] < x)
			return find(v->sons[1], x);
		else
			return find(v->sons[0], x);
	} else {

		if (v->keys[1] < x)
			return find(v->sons[2], x);
		else if (v->keys[0] < x)
			return find(v->sons[1], x);
		else
			return find(v->sons[0], x);
	}
}


// make new insert
Node* insert(Node* v, int x) {
	if (!v)
		return new Node(x);
	if (x < v->val)
		v->L = insert(v->L, x);
	else if (v->val < x)
		v->R = insert(v->R, x);
	return v;
}







Node* next(Node* v, int x) {
	if (!v)
		return v;
	if (x < v->val) {
		Node* ans = next(v->L, x);
		return ans ? ans : v;
	} else {
		return next(v->R, x);
	}
}


Node* prev(Node* v, int x) {
	if (!v)
		return v;
	if (v->val < x) {
		Node* ans = prev(v->R, x);
		return ans ? ans : v;
	} else {
		return prev(v->L, x);
	}
}


Node* erase(Node* v, int x) {
	if (!v)
		return v;
	if (v->val == x) {
		Node v2 = (*v);
		delete v;
		if (!v2.L)
			return v2.R;
		Node* p = v2.L;
		while (p->R) {
			p = p->R;
		}
		p->R = v2.R;
		return v2.L;
	} else if (x < v->val) {
		v->L = erase(v->L, x);
	} else {
		v->R = erase(v->R, x);
	}
	return v;
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("lis.in", "r", stdin), freopen("lis.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	Node* tree = nullptr;
	string s;
	int x;
	while (cin >> s >> x) {
		// cout << s << endl;
		if (s[0] == 'i') {
			tree = insert(tree, x);
		} else if (s[0] == 'e') {
			cout << (find(tree, x) ? "true\n" : "false\n");
		} else if (s[0] == 'n') {
			out_val(next(tree, x));
		} else if (s[0] == 'p') {
			out_val(prev(tree, x));
		} else if (s[0] == 'd') {
			tree = erase(tree, x);
		}
		// out_tree(tree);
		// cout << endl;
	}

	return 0;
}
