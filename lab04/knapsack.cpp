#include <cmath>
#include <algorithm>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

ifstream in("knapsack.in");
ofstream out("knapsack.out");

int a[1002][10002];
void massiv_out(int n, int m) {
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++)
			cerr << a[i][j] << " ";

		cerr << endl;
	}
	cerr << endl;
}
int main() {
	int n, m;
	in >> n >> m;
	vector<int> mas(n + 1), price(n + 1);
	for (int i = 1; i <= n; i++)
		in >> mas[i];
	for (int i = 1; i <= n; i++)
		in >> price[i];
	for (int i = 1; i <= n; i++) {
		for (int maxh = 1; maxh <= m; maxh++) {
			if (mas[i] <= maxh)
				a[i][maxh] = max(a[i - 1][maxh],
						a[i - 1][maxh - mas[i]] + price[i]);
			else
				a[i][maxh] = a[i - 1][maxh];
			// massiv_out(n, m);
		}
		// massiv_out(n, m);
	}
	stack<int> ans;
	for (int i = n; i >= 1; i--)
		if (a[i][m] != a[i - 1][m]) {
			m -= mas[i];
			ans.push(i);
		}
	out << ans.size() << "\n";
	while (!ans.empty()) {
		out << ans.top() << " ";
		ans.pop();
	}
	return 0;
}

