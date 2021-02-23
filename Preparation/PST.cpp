//#pragma once
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(),v.end()
#define nl '\n'
#define prt(x) #x<<": "<<x<<nl
#define pb push_back

//PST
const int N = 1e6+3;
int rng,root[N],pv;
vector<int> L,R,tree;
//Need Initialization: set rng and call build() once
void build(int id=1,int s=0,int e=rng){
	L.pb(0); R.pb(0); tree.pb(0);
	//if we don't need build
	if(1) return;
	if(e-s<=1){ 
		//init tree[id]
		//tree[id] = 0;
		return;
	}
	L[id] = ++pv; R[id] = ++pv;
	int m = (0LL+s+e)/2;
	build(L[id],s,m); build(R[id],m,e);
}
int upd_new(int p,int v,int id,int s,int e){
    if(p<s || e<=p) return id;
	int nid = ++pv;
	L.pb(0); R.pb(0); tree.pb(0);
	if(e-s<=1){
		tree[nid] =  v;
		return nid;
	}
	int m = (0LL+s+e)/2;
	L[nid] = upd_new(p,v,L[id],s,m);
    R[nid] = upd_new(p,v,R[id],m,e);
	tree[nid] = tree[L[nid]] + tree[R[nid]];
	return nid;
}
void upd_new(int id1,int id2,int p,int v){
	root[id1] = upd_new(p,v,root[id2],0,rng);
}
void upd_new(int id,int p,int v){
	upd_new(id,id-1,p,v);
}
//Use only when updating the same nodes
int upd_old(int p,int v,int id,int s,int e){
    if(p<s || e<=p) return id;
	int nid = id;
	if(id==0){
		nid = ++pv;
		L.pb(0); R.pb(0); tree.pb(0);
	}
	if(e-s<=1){
		tree[nid] = v;
		return nid;
	}
	int m = (0LL+s+e)/2;
	L[nid] = upd_old(p,v,L[id],s,m);
    R[nid] = upd_old(p,v,R[id],m,e);
	tree[nid] = tree[L[nid]] + tree[R[nid]];
	return nid;
}
void upd_old(int id,int p,int v){
	upd_old(p,v,root[id],0,rng);
}
bool isOn(int X,int bit){
	return X & (1<<bit);
}
int qry_XorMax(int X,int idL,int idR,int bit,int s=0,int e=rng){
    if(e-s<=1) return s;
    int m = (0LL+s+e)/2;
	int Lval = tree[L[idR]] - tree[L[idL]];
	int Rval = tree[R[idR]] - tree[R[idL]];
	if(isOn(X,bit)){
		if(Lval>0) return qry_XorMax(X,L[idL],L[idR],bit-1,s,m);
		else return qry_XorMax(X,R[idL],R[idR],bit-1,m,e);
	}else{
		if(Rval>0) return qry_XorMax(X,R[idL],R[idR],bit-1,m,e);
		else return qry_XorMax(X,L[idL],L[idR],bit-1,s,m);
	}
}
int qry_Sum(int l,int r,int id,int s=0,int e=rng){
	if(r<=s || e<=l) return 0;
	if(l<=s && e<=r) return tree[id];
	int m = (0LL+s+e)/2;
	int res = 0;
	if(L[id]) res += qry_Sum(l,r,L[id],s,m);
	if(R[id]) res += qry_Sum(l,r,R[id],m,e);
	return res;
}
int qry_Kth(int k,int idL,int idR,int s=0,int e=rng){
    if(e-s<=1) return s;
    int m = (0LL+s+e)/2;
	int Lval = tree[L[idR]] - tree[L[idL]];
    if(Lval>=k) return qry_Kth(k,L[idL],L[idR],s,m);
    else return qry_Kth(k-Lval,R[idL],R[idR],m,e);
}
int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n; cin>>n;
	vector<int> v(n),t;
	for(int i=0;i<n;i++) cin>>v[i];
	t=v;
	sort(all(t)); t.erase(unique(all(t)),t.end());

	//PST init
	rng = n; build();

	vector<int> chk(t.size(),-1);
	for(int i=0;i<n;i++){
		v[i] = lower_bound(all(t),v[i]) - t.begin();
		//(i+1)th update
		upd_new(i+1,i,1);
		upd_new(i+1,i+1,chk[v[i]],0);
		chk[v[i]] = i;
	}
	int Q; cin>>Q;
	int ans = 0;
	while(Q--){
		int l,r; cin>>l>>r;
		l += ans;
		ans = qry_Sum(l-1,r,root[r]);
		cout<<ans<<nl;
	}
}
