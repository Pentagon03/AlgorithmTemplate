#define pb push_back
const int inf = 1e9 + 1;

//PST
struct PST{
	vector<int> root,L,R,tree;
	int pv = 0, init = 0;
	PST(int n = 0) {
		root.resize(n+1);
		build();
	}
	void build(int id=0,int s=0,int e=inf){
		L.pb(0); R.pb(0); tree.pb(0);
		//if we don't need build
		if(!init) return;
		if(e-s<=1){ 
			//init tree[id]
			//tree[id] = 0;
			return;
		}
		L[id] = ++pv; R[id] = ++pv;
		int m = (0LL+s+e)/2;
		build(L[id],s,m); build(R[id],m,e);
	}
	int upd_new(int p,int v,int id,int s=0,int e=inf){
		if(p<s || e<=p) return id;
		int nid = ++pv;
		L.pb(0); R.pb(0); tree.pb(0);
		if(e-s<=1){
			tree[nid] += v;
			return nid;
		}
		int m = (0LL+s+e)/2;
		L[nid] = upd_new(p,v,L[id],s,m);
		R[nid] = upd_new(p,v,R[id],m,e);
		tree[nid] = tree[L[nid]] + tree[R[nid]];
		return nid;
	}
	int upd_root2(int t1, int t2 ,int p,int v,int s=0,int e=inf){
		assert(0 <= t2 && t2 < t1 && t1 < root.size());
		return root[t1] = upd_new(p,v,root[t2],s,e);
	}
	int upd_root(int p,int v,int s=0,int e=inf){
		root.pb(upd_new(p,v,root.back(),s,e));
		return root.back();
	}
	int chg(int k){
		assert(0<=k && k<root.size());
		return root[k];
	}
	bool isOn(int X,int bit){
		return X & (1<<bit);
	}
	int qry_XorMax(int X,int idL,int idR,int bit,int s=0,int e=inf){
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
	int qry_Sum(int l,int r,int id,int s=0,int e=inf){
		if(r<=s || e<=l) return 0;
		if(l<=s && e<=r) return tree[id];
		int m = (0LL+s+e)/2;
		int res = 0;
		if(L[id]) res += qry_Sum(l,r,L[id],s,m);
		if(R[id]) res += qry_Sum(l,r,R[id],m,e);
		return res;
	}
	int qry_Kth(int k,int idL,int idR,int s=0,int e=inf){
		if(e-s<=1) return s;
		int m = (0LL+s+e)/2;
		int Lval = tree[L[idR]] - tree[L[idL]];
		if(k<=Lval) return qry_Kth(k,L[idL],L[idR],s,m);
		else return qry_Kth(k-Lval,R[idL],R[idR],m,e);
	}
};
