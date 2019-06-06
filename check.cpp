#include <bits/stdc++.h>
#define ll long long

using namespace std;

ifstream in1("a.out");
ifstream in2("a2.out");

int main() {
	//*/

	string ans1, ans2;
	int i = 0;
	while (in1 >> ans1) {
		in2 >> ans2;
		++i;
		if (ans1 != ans2) {
			cerr << " !!BAD!!!\n" <<  i << "\n\n!!!";

		}
	}
	
	cerr << "ok\n";
	return 0;
	//*/
}