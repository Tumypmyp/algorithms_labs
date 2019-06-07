#include <iostream>

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

	void push(int v) {
		Node* new_end = new Node(v);
		new_end->next = end;
		end = new_end;
	}
	void pop() {
		Node* new_end = end->next;
		delete end;
		end = new_end;
	}
	int top() {
		return end->val;
	}
};


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	int n, v;
	char t;
	cin >> n;
	
	Stack a = Stack();
	
	for (int i = 0; i < n; ++i) {
		cin >> t;
		if (t == '-') {
			cout << a.top() << "\n";
			a.pop();
		} else {
			cin >> v;
			a.push(v);
		}
		// a.out();
		// cout << a.n << " - size\n";
	}

	return 0;
}