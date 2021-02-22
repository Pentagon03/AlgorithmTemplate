#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+10;

struct disjoint_set {
	vector<int> par;
	disjoint_set(int n=N) : par(n+1, -1) {}
	void init(int n=N) {
		fill(par.begin(), par.begin()+n+1, -1);
	}
	int find(int u) {
		return par[u] < 0 ? u : par[u] = find(par[u]);
	}
	bool merge(int u, int v) {
		u = find(u), v = find(v);
		if (u == v) return false;

		if (par[u] > par[v]) swap(u, v);
		par[u] += par[v];
		par[v] = u;
		return true;
	}
};
