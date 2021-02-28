int n,k;
int siz[N], A[1000010];
bool vis[N];
vector<pii> g[N];

#define ok(x) x!=p && !vis[x]
int get_siz(int v,int p=-1){
	siz[v] = 1;
	for(auto[nxt,w]:g[v]) if(ok(nxt))
		siz[v] += get_siz(nxt,v);
	return siz[v];
}

int get_cent(int v,int p,int S){
	for(auto[nxt,w]:g[v]) if(ok(nxt) && siz[nxt]*2>S) return get_cent(nxt,v,S);
	return v;
}

void dfs(int v,int p,int len,vector<int>&t){
	if(len>k) return;
	t.pb(len);
	for(auto[nxt,w]:g[v])
		if(ok(nxt))
			dfs(nxt,v,len+w,t);
}
ll dnc(int v){
	int cent = get_cent(v,-1,get_siz(v));
	vector<int> t;
	ll ans = 0;
	A[0] = 1;
	for(auto[nxt,w]:g[cent]){
		if(vis[nxt]) continue;
		t.clear();
		dfs(nxt,cent,w,t);
		for(auto l:t) ans += A[k-l];
	}
	for(auto l:t) A[l] = 0;
	vis[cent] = 1;
	for(auto[nxt,w]:g[cent]) if(!vis[nxt]) ans += dnc(nxt);
	return ans;
}


void solve(){
	cin>>n>>k; //길이가 k인 경로의 개수를 구한다
	rep(i,n-1){
		int a,b,w; cin>>a>>b>>w;
		g[a].eb(b,w); g[b].eb(a,w);
	}
	ll ans = dnc(0);
	cout<<ans<<nl;
}
