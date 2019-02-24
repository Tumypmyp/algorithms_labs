#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N = 1e5 + 3;
ll k, n, ind[N];
double v[N], w[N];


bool isLess(double v1, double w1, double v2, double w2, double param) {
	return v1 - param * w1 < v2 - param * w2;
}

void swap2(ll index1, ll index2) {
	swap(v[index1], v[index2]);
	swap(w[index1], w[index2]);
	swap(ind[index1], ind[index2]);
}

void quickSort(ll left, ll right, double param) {
	ll l = left;
	ll r = right;
	double midV = v[(l + r) / 2];
	double midW = w[(l + r) / 2];
	do {
		while (isLess(midV, midW, v[l], w[l], param)) {
			l++;
		}
		while (isLess(v[r], w[r], midV, midW, param)) {
			r--;
		}
		if (l <= r) {
			swap2(l, r);
			l++;
			r--;
		}
	} while (l < r);
	if (left < r) {
		quickSort(left, r, param);
	}
	if (l < right) {
		quickSort(l, right, param);
	}
}

bool canBuild(double param) {
	quickSort(0, n - 1, param);
	double sumV = 0;
	double sumW = 0;
	for (ll i = 0; i < k; i++) {
		sumV += v[i];
		sumW += w[i];
	}
	return (double)sumV / (double)sumW >= param;
}

void binSearch() {
	double left = 0;
	double right = 1e7;
	for (ll i = 0; i < 60; i++) {
		double mid = (left + right) / 2;
		if (canBuild(mid)) {
			left = mid;
		} else {
			right = mid;
		}
	}
	quickSort(0, n - 1, left);
	for (ll i = 0; i < k; i++) {
		cout << ind[i] << endl;
	}
}

int main() {
	freopen("kbest.in", "r", stdin), freopen("kbest.out", "w", stdout);
	cin.tie(0), cout.tie(0), ios_base::sync_with_stdio(0);
	cin >> n >> k;
	for (ll i = 0; i < n; i++) {
		cin >> v[i] >> w[i];
		ind[i] = i + 1;
	}
	binSearch();
	return 0;
}
