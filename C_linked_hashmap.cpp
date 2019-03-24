#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int H = 2e6, BIG = 1e9 + 7, MOD = 9369319, P = 29;


int myhash(string s) {
	int h = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		h *= P;
		h += s[i] - 'a' + 1;
		h %= MOD;
	}
	h = h % H + H;
	return h % H;
}


struct Node {
	Node* prev;
	Node* next;
	string key, val;
	Node(string a, string b, Node* last = nullptr) {
		key = a;
		val = b;
		prev = last;
		next = nullptr;
	}
};

vector<Node*> a[H];
Node* last = nullptr;

void connect(Node* v1, Node* v2) {
	if (v1)
		v1->next = v2;
	if (v2)
		v2->prev = v1;
}

bool exists(string v) {
	for (auto &p : a[myhash(v)])
		if (p->key == v)
			return true;
	return false;
}

Node* get(string v) {
	for (auto &p : a[myhash(v)])
		if (p->key == v)
			return p;
	return nullptr;
}

void put(string v, string x) {
	if (!exists(v)) {
		Node* v2 = new Node(v, x);
		connect(last, v2);
		last = v2;
		a[myhash(v)].push_back(last);
	} else {
		for (auto &p : a[myhash(v)])
			if (p->key == v)
				p->val = x;
	}
}

void erase(string v) {
	auto &p = a[myhash(v)];
	for (int i = 0; i < (int)p.size(); ++i)
		if (p[i]->key == v) {
			if (p[i] == last)
				last = p[i]->prev;
			connect(p[i]->prev, p[i]->next);
			delete p[i];
			p.erase(p.begin() + i);
			return;
		}
}

void out_node(Node* v) {
	cout << (v ? v->val : "none") << endl;
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("linkedmap.in", "r", stdin), freopen("linkedmap.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string t, x, y;
	while (cin >> t >> x) {
		if (t == "put") {
			cin >> y;
			put(x, y);
		} else if (t[0] == 'd') {
			erase(x);
		} else if (t[0] == 'g') {
			out_node(get(x));
		} else if (t == "prev") {
			if (exists(x))
				out_node(get(x)->prev);
			else
				cout << "none\n";
		} else if (t == "next") {
			if (exists(x))
				out_node(get(x)->next);
			else
				cout << "none\n";
		}
	}
	return 0;
}
