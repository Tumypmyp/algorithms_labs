#include <bits/stdc++.h>

using namespace std;

const int BIG = 1e9 + 7;


struct Node{
	int v, degree, ind;
	Node* par;
	Node* child; 
	Node* sibl;
	Node* un_sibl;
	Node(int v0, int i){
		v = v0;
		ind = i;
		degree = 0;
		par = nullptr;
		child = nullptr;
		sibl = nullptr;
		un_sibl = nullptr;
	}

	void out_node() {
		cout << "(" << v << " " << ind << " " << degree << "): {";
		Node* i = child;
		while (i) {
			i->out_node();
			i = i->sibl;
		}
		cout << "}  ";
	}

	void add(Node* n2) {
		++degree;
		n2->par = this;
		if (child)
			child->un_sibl = n2;
		n2->sibl = child;
		child = n2;
	}

	bool operator< (const Node &n2) const{
		return v < n2.v || (v == n2.v && ind < n2.ind);
	}
};








struct Tree{
	Node* head;
	Tree() {
		head = nullptr;
	}
	void merge(Tree &b) {
		cout << "1: "; out_tree();
		cout << "2: "; b.out_tree();
		cout << "-merge" << endl;
		//*/
		if (!head) {
			head = b.head;
			b.head = nullptr;
			return;
		}
		if (!b.head)
			return;
		vector<Node*> sum;
		Node* a_i = head;
		Node* b_i = b.head;
		while (a_i && b_i) {
			if (a_i->degree < b_i->degree) {
				sum.push_back(a_i);			
				a_i = a_i->sibl; 
			} else {
				sum.push_back(b_i);
				b_i = b_i->sibl; 	
			}
		}
		while (a_i) {
			sum.push_back(a_i);			
			a_i = a_i->sibl; 
		}
		while (b_i) {
			sum.push_back(b_i);
			b_i = b_i->sibl; 	
		}
		//*/
		for (auto p : sum) {
			p->out_node();
		}
		cout << "-sum1" << endl;;
		//*/
		vector<Node*> sum2;
		for (int i = 0; i < (int)sum.size(); ++i) {
			if (i + 1 < (int)sum.size() && sum[i]->degree == sum[i + 1]->degree) {
				if (sum[i + 1] < sum[i]) {
					swap(sum[i], sum[i + 1]);
				}
				/*/
				sum[i]->out_node();
				sum[i + 1]->out_node();
				cout << " - nodes " << endl;
				//*/
				sum[i]->add(sum[i + 1]);
				// cout << "added" << endl;
				sum2.push_back(sum[i]);
				++i;
				continue;
			}
			sum2.push_back(sum[i]);
		}
		
		//*/
		for (auto p : sum2) {
			p->out_node();
		}
		cout << "-sum2" << endl;;
		//*/
		head = sum2[0];
		Node* sum_i = head;
		for (int i = 0; i < (int)sum2.size() - 1; ++i) {
			sum_i->sibl = sum2[i + 1];
			sum2[i + 1]->un_sibl = sum_i;
		}
		b.head = nullptr;
		// out_tree();
		// cout << "merged\n\n";
	}
	
	Node* insert(int v, int ind) {
		Tree b;
		b.head = new Node(v, ind);
		Node* k = b.head;
		merge(b);
		return k;
	}

	Node* get_min() {
		Node* min_node = head;
		Node* i = head;
		while (i) {
			cout << i->v << " ";
			if ((*i) < (*min_node))
				min_node = i;
			i = i->sibl;
		}
		cout << min_node->v << " what's the min?" << endl;
		return min_node;
	}

	void delete_min(){
		Node* i = get_min();
		if (i->un_sibl)
			i->un_sibl->sibl = i->sibl;
		if (i->sibl)
			i->sibl->un_sibl = i->un_sibl;
		Tree sons;
		sons.head = i->child;
		delete i;
		merge(sons);

	}
	void out_tree() {
		Node* i = head;
		while (i) {
			i->out_node();
			cout << " ";
			i = i->sibl;
		}
		cout << "\n" << endl;

	}

};


void update(Node* i, int v) {
	i->v = v;
	while (i->par && (*i) < (*i->par)) {
		swap(i->v, i->par->v);
		swap(i->ind, i->par->ind);
		i = i->par;
	}
	while (i->child && (*i->child) < (*i)) {
		swap(i->v, i->child->v);
		swap(i->ind, i->child->ind);
		i = i->child;
	}
}




int main() {
	#ifdef ON_PC
		freopen("a.in", "r", stdin), freopen("a.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

	int n, m, ind = 1, t, u, v;
	cin >> n >> m;
	vector<Tree> a(n + 1);
	//*/
	for (int j = 1; j <= n; ++j) {
		a[j].out_tree();
		cout << "\n" << endl;
	}
	//*/
	vector<Node*> it_by_ind(1, nullptr);
	for (int i = 0; i < m; ++i) {
		cin >> t;
		cout << i << " :: " << t << endl;
		if (t == 0) {
			cin >> u >> v;
			it_by_ind.push_back(a[u].insert(v, ind++));
		} else if (t == 1) {
			cin >> u >> v;
			a[v].merge(a[u]);
		} else if (t == 2) {
			cin >> u;
			update(it_by_ind[u], -BIG);
			cout << it_by_ind[u]->v << " - v was" << endl;
			Node* h = it_by_ind[u];
			while (h->par) {
				h = h->par;
			}
			while (h->un_sibl) {
				h = h->un_sibl;
			}
			h->delete_min();
		} else if (t == 3) {
			cin >> u >> v;
			update(it_by_ind[u], v);
		} else if (t == 4) {
			cin >> u;
			cout << a[u].get_min()->v << "\n";
		} else if (t == 5) {
			cin >> u;
			a[u].delete_min();
		}

		//*/
		cout << "////////\n";
		for (int j = 1; j <= n; ++j) {
			cout << j << " "; 
			a[j].out_tree();
			cout << "\n" << endl;
		}
		//*/
	}
	return 0;
}
