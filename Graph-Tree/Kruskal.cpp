const int N = 1e5+5, inf = 1e9, mod = 1e9+7;

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
}f;
void solve(){
	int n,m; cin>>n>>m;
    vector<tuple<int,int,int>> E;
    rep(i,m){
        int a,b,c; cin>>a>>b>>c;
        E.emplace_back(c,a,b);
    }
    f.init(n);
    sort(all(E));
    ll ans = 0;
    for(auto[c,a,b]:E){
        if(f.merge(a,b)) ans += c;	
    }
    cout<<ans<<'\n';
}
