#include <bits/stdc++.h>

using namespace std;

const int P = 26, M = 256, MOD = 65536; 

int string_to_int(string s) {
	stringstream ss;
	ss << s;
	int ans;
	ss >> ans;
	return ans;
}


template <typename T>

struct Dequeue {
	int n, L, R, size;
	T *begin = nullptr;

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
		T *new_begin = new T[new_n];
		for (int i = 0, j = L; j != R && i < new_n; ++i, j = next_ind(j))
			new_begin[i] = begin[j];
		n = new_n;
		R = size;
		L = 0;
		delete [] begin;
		begin = new_begin;
	}

	void push_front(T v) {
		if (pref_ind(L) == R) {
			resize(n * 2);
		}
		L = pref_ind(L);
		begin[L] = v;
		++size;
	}
	void push_back(T v) {
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

	T back() {
		return empty() ? 0 : begin[pref_ind(R)];
	}
	T front() {
		return empty() ? 0 : begin[L];
	}

	T pfront() {
		T ans = front();
		pop_front();
		return ans;
	}

	T get(int ind) {
		if (ind >= size)
			return 0;
		ind = (ind + L) % n;
		return begin[ind];

	}
	void insert(int ind, T v) {
		if (ind >= size)
			return;
		ind = (ind + L) % n;
		begin[ind] = v;
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





int modulo(int a, int mod) {
	return (a % mod + mod) % mod;
}


Dequeue<string> a;
Dequeue<int> q, next_ind;
int reg[P];

void go(int i) {
	if (i >= a.size)
		return;
	// q.out("q");

	string s = a.get(i);
	if (s[0] == '+') {
		int x = q.pfront();
		int y = q.pfront();
		int ans = x + y;
		q.push_back(modulo(ans, MOD));
	} else if (s[0] == '-') {
		int x = q.pfront();
		int y = q.pfront();
		int ans = x - y;
		q.push_back(modulo(ans, MOD));
	} else if (s[0] == '*') {
		int x = q.pfront();
		int y = q.pfront();
		int ans = x * y;
		q.push_back(modulo(ans, MOD));
	} else if (s[0] == '/') {
		int x = q.pfront();
		int y = q.pfront();
		int ans = (y == 0 ? x : x / y);
		q.push_back(modulo(ans, MOD));
	} else if (s[0] == '%') {
		int x = q.pfront();
		int y = q.pfront();
		int ans = (y == 0 ? x : x % y);
		q.push_back(modulo(ans, MOD));
	} else if (s[0] == '>') {
		int x = q.pfront();
		reg[s[1] - 'a'] = x;
	} else if (s[0] == '<') {
		q.push_back(reg[s[1] - 'a']);
	} else if (s.size() == 1 && s[0] == 'P') {
		int x = q.pfront();
		cout << x << "\n";	
	} else if(s[0] == 'P') {
		cout << reg[s[1] - 'a'] << "\n";
	} else if (s.size() == 1 && s[0] == 'C') {
		int x = q.pfront();
		cout << char(modulo(x, M));
	} else if (s[0] == 'C') {
		cout << char(modulo(reg[s[1] - 'a'], M));
	} else if (s[0] == ':') {

	} else if (s[0] == 'J') {
		go(next_ind.get(i));
		return;
	} else if (s[0] == 'Z') {
		if (reg[s[1] - 'a'] == 0) {
			go(next_ind.get(i));
			return;
		}
	} else if (s[0] == 'E') {
		if (reg[s[1] - 'a'] == reg[s[2] - 'a']) {
			go(next_ind.get(i));
			return;
		}
	} else if (s[0] == 'G') {
		if (reg[s[1] - 'a'] > reg[s[2] - 'a']) {
			go(next_ind.get(i));
			return;
		}
	} else if (s[0] == 'Q') {
		exit(0);
	} else if ('0' <= s[0] && s[0] <= '9') {
		q.push_back(string_to_int(s) % MOD);
	}
	go(i + 1);
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	
	string s;
	while (cin >> s) {
		a.push_back(s);
		next_ind.push_back(-1);
	}
	for (int i = 0; i < a.size; ++i) {
		if (a.get(i)[0] == ':') {
			s = a.get(i);
			s = s.substr(1, s.size() - 1);
			for (int j = 0; j < a.size; ++j) {
				string s2 = a.get(j);
				if (s2[0] == 'J' && s == s2.substr(1, min(s.size(), s2.size() - 1))) {
					next_ind.insert(j, i);
				} else if (s2[0] == 'Z' && s == s2.substr(2, min(s.size(), s2.size() - 2))) {
					next_ind.insert(j, i);
				} else if ((s2[0] == 'E' || s2[0] == 'G') && s == s2.substr(3, min(s.size(), s2.size() - 3))) {
					next_ind.insert(j, i);
				}

			}
		}
	}

	// a.out();
	go(0);
	return 0;

}