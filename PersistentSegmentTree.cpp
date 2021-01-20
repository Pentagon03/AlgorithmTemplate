#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+5;
int n,root[N],L[N*20],R[N*20],a[N],pv;
ll tree[N*20];
void build(int id=0,int s=0,int e=n){
	if(e-s<=1){
		tree[id] = a[s];
		return;
	}
	int m = s + e >> 1;
	build(L[id]=++pv,s,m); build(R[id]=++pv,m,e);
	tree[id] = tree[L[id]] + tree[R[id]];
}
int upd(int p,int v,int id,int s,int e){
	int nid = ++pv;
	if(e-s<=1){
		tree[nid] = (a[p]=v);
		return nid;
	}
	int m = s + e >> 1;
	L[nid] = L[id]; 
	R[nid] = R[id];
	if(p<m) L[nid] = upd(p,v,L[id],s,m);
	else R[nid] = upd(p,v,R[id],m,e);
	tree[nid] = tree[L[nid]] + tree[R[nid]];
	return nid;
}
int upd(int p,int v,int k){
	return root[k] = upd(p,v,root[k-1],0,n);
}
ll qry(int l,int r,int id,int s=0,int e=n){
	if(l>=e || s>=r) return 0;
	if(l<=s && e<=r) return tree[id];
	int m = s + e >> 1;
	return qry(l,r,L[id],s,m) + qry(l,r,R[id],m,e);
}
int main(){
    ios::sync_with_stdio(!cin.tie(0));
    cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	build();
	int k=0,Q; cin>>Q;
	while(Q--){
		int t,a,b,c; cin>>t>>a>>b;
		if(t==1)
			upd(--a,b,++k);
		else
			cin>>c, cout<<qry(--b,c,root[a])<<'\n';
	}
}
