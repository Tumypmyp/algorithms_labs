
const int MAXN = 1 << 16;


int t, n, a, b;

unsigned int cur = 0;
unsigned int nextRand24() {
	cur = cur * a + b;
	return cur >> 8;
}

unsigned int nextRand32 {
	unsigned int a = nextRand24(), b = nextRand24();
	return (a << 8) ^ b
}


int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> t >> n >> a >> b;
	vector<pair<int, int> c(n)
	vector<vector<pair<int, int>>> cnt (MAXN);
	for (int i = 0; i < n; ++i) {
		c[i] = nextRand32();

	}
	int ind = 0;
	for (int mask = 0; mask < cnt.size(); ++mask) {

	}

	return 0;
}
