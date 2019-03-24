#include <iostream>

using namespace std;

struct Queue {
	int n, L, R;
	int *begin = nullptr;


	void resize(int new_n) {
		new_n = max(1, new_n);
		int *new_begin = new int[new_n];
		for (int i = 0, j = L; j < R && i < new_n; ++i, ++j)
			new_begin[i] = begin[j];
		n = new_n;
		R -= L;
		L = 0;
		delete [] begin;
		begin = new_begin;
	}

	Queue(int new_n = 1) {
		L = R = 0;
		resize(new_n);		
	}

	int size() {
		return R - L;
	}
	bool empty() {
		return size() == 0;
	}
	void push(int v) {
		if (R >= n) {
			resize(size() * 2);
		}
		begin[R++] = v;
	}
	void pop() {
		++L;
		if (size() * 4 < n) {
			resize(n / 2);
		}
	}
	int back() {
		return empty() ? 0 : begin[R - 1];
	}
	int front() {
		return empty() ? 0 : begin[L];
	}

	void out() {
		for (int i = L; i < R; ++i)
			cout << begin[i] << " ";
		cout << "  " << n << " - queue" << endl;
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

	Queue a;
	for (int i = 0; i < n; ++i) {
		cin >> t;
		if (t == '-') {
			cout << a.front() << "\n";
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