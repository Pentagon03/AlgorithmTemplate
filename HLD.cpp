#include<bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
#define fi first
#define se second
#define all(v) v.begin(,v.end()

const int N = 1e5+5;
int par[N],dep[N],sz[N],in[N],out[N],pv,top[N];
vector<pii> g[N];
pii edge[N];

inline int op(int x,int y){return max(x,y);}
struct Seg{
	int n,t[2*N]={0,};
	Seg(int f=0):n(f){}
	void update(int p,int val){for(t[p+=n-1]=val;p>1;p>>=1)t[p>>1]=op(t[p],t[p^1]);}
	int query(int l,int r){
	    int res=0;
	    for(l+=n-1,r+=n-1;l<=r;l>>=1,r>>=1){
	        if(l&1) res = op(res,t[l++]);
	        if(!(r&1)) res = op(res,t[r--]);
	    }
	    return res;
	}
}f;


void dfs_sz(int v=1){
	sz[v] = 1; 
	dep[v] = dep[par[v]]+1;
	if(par[u]) g[u].erase(find(all(g[u]),par[u]));
	for(auto&u:g[v]){
		par[u.fi]=v;
		dfs_sz(u.fi);
		sz[v]+=sz[u.fi];
		if(sz[u.fi] > sz[g[v][0].fi])
			swap(u,g[v][0]);
	}
}

void dfs_hld(int v=1,int w=0){
	in[v] = ++pv;
	f.update(in[v],w);
	for(auto u:g[v]){
		top[u.fi]= u.fi==g[v][0].fi?top[v]:u.fi;
		dfs_hld(u.fi,u.se);
	}
	out[v]=pv;
}

int query(int a,int b){
	int ans=0;
	while(top[a]!=top[b]){
		if(dep[top[a]]>dep[top[b]]) swap(a,b);
		int st = top[b];
		ans = op(ans,f.query(in[st],in[b]));
		b=par[st];
	}
	if(dep[a]>dep[b]) swap(a,b);
	ans = op(ans,f.query(in[a]+1,in[b]));
	return ans;
}

int main(){
	ios::sync_with_stdio(!cin.tie(0));

	int n,m,a,b,c; cin>>n; 
	f = Seg(n);
	for(int i=1;i<n;i++){
		cin>>a>>b>>c;
		edge[i]=pii(a,b);
		g[a].push_back(pii(b,c));
		g[b].push_back(pii(a,c));
	}
	dfs_sz(); dfs_hld();
	cin>>m;
	while(m--){
		cin>>a>>b>>c;
		if(a==1){
			int p=edge[b].fi,q=edge[b].se;
			if(dep[p]>dep[q]) swap(p,q);
			f.update(in[q],c);
		}
		else cout<<query(b,c)<<'\n';
	}
}
