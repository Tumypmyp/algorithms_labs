#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define x first
#define y second
#define point pair<int, int>
#define mp make_pair

const int n = 1 << 24, BIG = 1e9 + 7;
int MOD = 1e9;

struct mtx {
	int a, b, c, d;
};

mtx tree[800013], a[200013];

mtx op(mtx a, mtx b) {
	mtx ans = {a.a * b.a + a.b * b.c,
		a.a * b.b + a.b * b.d,
		a.c * b.a + a.d * b.c,
		a.c * b.b + a.d * b.d};
	return {ans.a % MOD, ans.b % MOD, ans.c % MOD, ans.d % MOD};
}

void build(int v, int L, int R) {
	if (L + 1 == R) {
		tree[v] = a[L];
		return;
	}
	int mid = (L + R) / 2;
	build(v * 2, L, mid);
	build(v * 2 + 1, mid, R);
	tree[v] = op(tree[v * 2], tree[v * 2 + 1]);
}


mtx get_sum(int v, int L1, int R1, int L, int R) {
	if (R1 <= L || R <= L1)
		return {1, 0, 0, 1};
	if (L <= L1 && R1 <= R) {
		// cout << v->L << " " << v->R << "-" << v->val << ", ";
		return tree[v];
	}
	int mid = (L1 + R1) / 2;
	return op(get_sum(v * 2, L1, mid, L, R), get_sum(v * 2 + 1, mid, R1, L, R));
}

int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#else
		// freopen("set.in", "r", stdin), freopen("set.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> MOD >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> a[i].a >> a[i].b >> a[i].c >> a[i].d;
	}
	build(1, 0, n);
	int L, R;
	for (int i = 0; i < m; ++i) {
		cin >> L >> R; --L, --R;
		mtx ans = get_sum(1, 0, n, L, R + 1);
		printf("%d %d\n%d %d\n\n", ans.a, ans.b, ans.c, ans.d);
	}
	return 0;
}
