#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int N = 1007, BIG = 1e9 + 7, MOD = 9369319, P = 29;

//hash set of linked hashmapped strings

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

struct Set{
	static const int H = 101;
	vector<Node*> a[H];
	Node* last = nullptr;
	string key;
	int size;

	Set(string s) {
		size = 0;
		key = s;
	}

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
			size++;
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
				size--;
				return;
			}
	}
};


int myhash(string s) {
	int h = 0;
	for (int i = 0; i < (int)s.size(); ++i) {
		h *= P;
		h += s[i] - 'a' + 1;
		h %= MOD;
	}
	h = h % N + N;
	return h % N;
}

vector<Set*> a[N];

bool exists(string v) {
	for (auto &p : a[myhash(v)])
		if (p->key == v)
			return true;
	return false;
}

Set* get(string v) {
	for (auto &p : a[myhash(v)])
		if (p->key == v)
			return p;
	return nullptr;
}

void put(string v, string x) {
	if (!exists(v))
		a[myhash(v)].push_back(new Set(v));
	get(v)->put(x, "");
}

void erase_all(string v) {
	auto &p = a[myhash(v)];
	for (int i = 0; i < (int)p.size(); ++i)
		if (p[i]->key == v) {
			delete p[i];
			p.erase(p.begin() + i);
			return;
		}
}

void erase(string v, string s) {
	Set* p = get(v);
	if (!p)
		return;
	p->erase(s);
}

void out_set(Set* v) {
	Node* p = v->last;
	cout << v->size << " ";
	while (p) {
		cout << p->key << " ";
		p = p->prev;
	}
	cout << "\n";
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		freopen("multimap.in", "r", stdin), freopen("multimap.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string t, x, y;
	while (cin >> t >> x) {
		if (t == "put") {
			cin >> y;
			put(x, y);
		} else if (t == "delete") {
			cin >> y;
			erase(x, y);
		} else if (t[0] == 'g') {
			if (get(x))
				out_set(get(x));
			else
				cout << "0\n";
		} else if (t == "deleteall") {
			erase_all(x);
		}
	}

	return 0;
}
