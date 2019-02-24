#include <iostream>

typedef long long ll;

using namespace std;

struct Dequeue {
	int n, L, R, size;
	int *begin = nullptr;

	Dequeue(int new_n = 1) {
		n = size = L = R = 0;
		resize(new_n);		
	}

	bool empty() {
		return size == 0;
	}
	int next_ind(int i) {
		return (i + 1) % n;
	}
	int pref_ind(int i) {
		return (i - 1 + n) % n;
	}

	void resize(int new_n) {
		new_n = max(1, new_n);
		int *new_begin = new int[new_n];
		for (int i = 0, j = L; j != R && i < new_n; ++i, j = next_ind(j))
			new_begin[i] = begin[j];
		n = new_n;
		R = size;
		L = 0;
		delete [] begin;
		begin = new_begin;
	}

	void push_front(int v) {
		if (pref_ind(L) == R) {
			resize(n * 2);
		}
		L = pref_ind(L);
		begin[L] = v;
		++size;
	}
	void push_back(int v) {
		if (next_ind(R) == L) {
			resize(n * 2);
		}
		begin[R] = v;
		R = next_ind(R);
		++size;
	}

	void try_decrease() {
		/*/		
		if (size * 4 + 2 < n) {
			resize(n / 2);
		}
		//*/
	}

	void pop_back() {
		R = pref_ind(R);
		--size;
		try_decrease();
	}
	void pop_front() {
		L = next_ind(L);
		--size;
		try_decrease();
	}

	int back() {
		return empty() ? 0 : begin[pref_ind(R)];
	}
	int front() {
		return empty() ? 0 : begin[L];
	}

	void out_vector() {
		for (int i = 0; i < n; ++i)
			cout << begin[i] << " ";
		cout << "\n";
	}

	void out(string name = "queue", bool array = false) {
		if (array) {
			for (int i = 0; i < n; ++i)
				cout << begin[i] << " ";
			cout << " : " <<  L << " " << R << endl;	
		}
		for (int i = L; i != R; i = next_ind(i))
			cout << begin[i] << " ";
		cout << " : " << size << " - " + name << endl;
	}


};

struct Queue_min{
	Dequeue q, q_min;

	void push(int v) {
		q.push_back(v);
		while(!q_min.empty() && q_min.back() > v) {
			q_min.pop_back();
		}
		q_min.push_back(v);
	}

	void pop() {
		if (q.front() == q_min.front())
			q_min.pop_front();
		q.pop_front();
	}

	int get_min() {
		return q_min.front();
	}
};

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m, k, a, b, c;
	cin >> n >> m >> k >> a >> b >> c;
	int *x = new int[n];
	for (int i = 0; i < k; ++i) {
		cin >> x[i];
	}
	for (int i = k; i < n; ++i)
		x[i] = (a * x[i - 2] + b * x[i - 1] + c);

	Queue_min q; 

	for (int i = 0; i < m; ++i) 
		q.push(x[i]);

	
	ll ans = q.get_min();


	for (int i = m; i < n; ++i) {
		q.push(x[i]);
		q.pop();
		ans += (ll)q.get_min();
	}
	cout << ans;

	return 0;

}