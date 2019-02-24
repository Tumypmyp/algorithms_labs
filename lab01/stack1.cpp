#include <iostream>

using namespace std;


struct vector {
	int n, size;
	int *begin = nullptr;

	void resize(int new_n) {
		new_n = max(1, new_n);
		int *new_begin = new int[new_n];
		for (int i = 0; i < size && i < new_n; ++i)
			new_begin[i] = begin[i];
		n = new_n;
		delete [] begin;
		// begin = new_begin;
		if (begin) {
			begin = new_begin;
		}
	}

	vector(int new_n = 1) {
		size = 0;
		resize(new_n);		
	}

	void push_back(int v) {
		if (size >= n) {
			resize(n * 2);
		}
		begin[size++] = v;
	}
	void pop_back() {
		--size;
		if (size * 4 < n) {
			resize(n / 2);
		}
	}
	int back() {
		if (size == 0)
			return 0;
		return begin[size - 1];
	}

	void out() {
		for (int i = 0; i < size; ++i)
			cout << begin[i] << " ";
		cout << " - vector" << endl;
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
	vector a = vector();
	
	for (int i = 0; i < n; ++i) {
		cin >> t;
		if (t == '-') {
			cout << a.back() << "\n";
			a.pop_back();
		} else {
			cin >> v;
			a.push_back(v);
		}
		// a.out();
		// cout << a.n << " - size\n";
	}
	4[a]
	return 0;
}