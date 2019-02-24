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
	char a;
	Stack q = Stack();
	while (cin >> a) {
		if ('0' <= a && a <= '9') {
			q.push(a - '0');
		} else {
			int x, y;
			y = q.top();
			q.pop();
			x = q.top();
			q.pop();
			if (a == '+')
				q.push(x + y);
			if (a == '*')
				q.push(x * y);
			if (a == '-')
				q.push(x - y);
			if (a == '/')
				q.push(x / y);
		}
	}

	cout << q.top();
	return 0;
}