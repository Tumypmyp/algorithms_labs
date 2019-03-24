#include <bits/stdc++.h>

using namespace std;


int sz = 0;

vector<int> a(1), ind(1), place(1);


void out() {
	cout << sz << "\n";
	for (auto &p : a)
		cout << p << " ";
	cout << "\n";
	for (auto &p : ind)
		cout << p << " ";
	cout << "\n";
	for (auto &p : place)
		cout << p << " ";
	cout << "\n\n";
	//*/
}

void big_swap(int x, int y) {
	swap(a[x], a[y]);
	swap(ind[x], ind[y]);
	swap(place[ind[x]], place[ind[y]]);
}

void refresh_up(int x) {
	// out();
	while (x > 1) {
		if (a[x] < a[x / 2]) {
			big_swap(x, x / 2);
			x /= 2;
		} else {
			break;
		}
		// out();
	}
}

void refresh_down(int x) {
	while (x * 2 <= sz) {
		if (x * 2 + 1 <= sz) {
			int y = x * 2;
			if (a[y] > a[y + 1])
				y++;
			if (a[y] < a[x]) {
				big_swap(y, x);
				x = y;
			} else {
				break;
			}
		} else {
			if (a[x * 2] < a[x]) {
				big_swap(x * 2, x);
				x *= 2;
			} else {
				break;
			}
		}
	}
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	string s;
	int x, y;
	while (cin >> s) {
		// cout << s << "\n";
		if (s[0] == 'p') {
			cin >> x;
			sz++;
			ind.push_back((int)place.size());
			place.push_back(sz);
			a.push_back(x);
			refresh_up(sz);
		} else {
			place.push_back(0);
			if (s[0] == 'e') {
				if (sz == 0) {
					cout << "*\n";
					continue;
				}
				cout << a[1] << " " << ind[1] << "\n";
				big_swap(1, sz);
				place[ind[sz]] = 0;
				a.pop_back();
				ind.pop_back();
				sz--;
				// out();
				if (sz > 0)
					refresh_down(1);
			} else {
				cin >> x >> y;
				// out();
				// cout << x << "th = " << y << "\n";
				a[place[x]] = y;
				refresh_up(place[x]);
				// out();
			}
		}
		// out();
	}
	return 0;
}
