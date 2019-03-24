#include <bits/stdc++.h>

using namespace std;
 
 
struct Node {
	Node* next;
	int val;
	Node(int v = 0) {
		val = v;
	}
};
 
struct Stack {
	int size;
	Node* end = nullptr;
 
	Stack() {
		size = 0;
		end = nullptr;
	}
 
	void push(int v) {
		Node* new_end = new Node(v);
		new_end->next = end;
		end = new_end;
		++size;
	}
	void pop() {
		Node* new_end = end->next;
		delete end;
		end = new_end;
		--size;
	}
	int top() {
		return end->val;
	}
	void clear() {
		while (size > 0) {
			pop();
		}
	}
};
 
 
 
map<int, int> br = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
	 
int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	Stack q = Stack();
	while (true) {
		s = s + "+";
		cout << s << endl; 
	}
	while (getline(cin, s)) {
		bool ok = true;
		for (auto &ch : s) {
			if (br.count(ch) > 0) {
				q.push(ch);
				// cout << ch << "+";
			} else {
				// cout << ch << "-";
				if (q.size > 0 && br[q.top()] == ch) {
					q.pop();
				} else {
					ok = false;
					break;
				}
			}
		}
		cout << (q.size == 0 && ok ? "YES\n" : "NO\n");
		q.clear();
	}
	return 0;
}