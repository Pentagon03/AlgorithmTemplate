//Solution to "https://www.acmicpc.net/problem/11932"
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(),v.end()
#define nl '\n'
#define prt(x) #x<<": "<<x<<nl
#define pb push_back
const int N = 1e5+5, lN = 17;
int rng,root[2*N],pv;
vector<int> L,R,tree;

//must call it once
//note that we can put large values on e
void build(int id=1,int s=0,int e=rng){
	L.pb(0); R.pb(0); tree.pb(0);
	//if we don't need build
	if(1) return;
	if(e-s<=1){
		//init tree[id];
		return;
	}
	L[id] = ++pv; R[id] = ++pv;
	int m = (0LL+s+e)/2;
	build(L[id],s,m); build(R[id],m,e);
}
int upd(int p,int v,int id,int s,int e){
	if(p<s||e<=p) return id;
	int nid = ++pv;
	L.pb(0); R.pb(0); tree.pb(0);
	if(e-s<=1){
		tree[nid] =  tree[id]+v;
		return nid;
	}
	int m = (0LL+s+e)/2;
	L[nid] = upd(p,v,L[id],s,m);
   	R[nid] = upd(p,v,R[id],m,e);
	tree[nid] = tree[L[nid]] + tree[R[nid]];
	return nid;
}
void upd(int id,int p,int v){
	root[id] = upd(p,v,root[id-1],0,rng);
}
int qry_sum(int l,int r,int id,int s=0,int e=rng){
	if(r<s || e<l) return 0;
	if(l<=s && e<=r) return tree[id];
	int m = (0LL+s+e)/2;
	int res = 0;
	if(L[id]) res += qry_sum(l,r,L[id],s,m);
	if(R[id]) res += qry_sum(l,r,R[id],m+1,e);
	return res;
}
int qry_kth(int k,int id1,int id2,int idlca,int v,int s=0,int e=rng){
    if(e-s<=1) return s;
    int m = (0LL+s+e)/2;
	int Lval = tree[L[id1]] + tree[L[id2]] - 2*tree[L[idlca]] + (s<=v && v<m);
    if(Lval>=k) return qry_kth(k,L[id1],L[id2],L[idlca],v,s,m);
    else return qry_kth(k-Lval,R[id1],R[id2],R[idlca],v,m,e);
}

int in[N],ID,par[N][lN],dep[N],val[N];
vector<int> g[N];
void dfs(int k=1,int p=0){
    upd(in[k]=++ID,val[k],1);
	dep[k] = dep[p]+1;
    par[k][0] = p;
    int pp = p, t = 1;
    while(par[pp][t-1]){
        pp = par[k][t] = par[pp][t-1];
        ++t;
    }
	for(int nxt:g[k])if(nxt!=p){
		dfs(nxt,k);
	}
    upd(++ID,val[k],-1);
}
int LCA(int a,int b,int&dis){
    if(dep[a]<dep[b]) swap(a,b);
    int dif = dep[a] - dep[b];
    dis = dif;
    for(int i=0;dif;(dif>>=1),i++){
        if(dif&1)
            a = par[a][i];
    }
    if(a==b) return a;
    for(int i=lN-1;i>=0;i--)
        if(par[a][i]!=par[b][i])
            a = par[a][i], b = par[b][i] , dis += (1<<i+1);
    dis += 2;
    return par[a][0];
}
int LCA(int a,int b){int t;return LCA(a,b,t);}
int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n,m; cin>>n>>m;
    vector<int> t;
	for(int i=1;i<=n;i++) cin>>val[i],t.push_back(val[i]);
    sort(all(t)); t.erase(unique(all(t)),t.end());
    for(int i=1;i<n;i++){
        int a,b; cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i=1;i<=n;i++) val[i] = lower_bound(all(t),val[i]) - t.begin();
    rng = t.size();
    build(); dfs(); 
    while(m--){
        int x,y,k; cin>>x>>y>>k;
        int L = LCA(x,y); 
        //cout<<prt(qry_kth(k,root[in[x]],root[in[y]],root[in[L]],val[L]));
        cout<<t[qry_kth(k,root[in[x]],root[in[y]],root[in[L]],val[L])]<<'\n';
    }
}
