#define pb push_back
const int N = 1e6+3, inf = 1e9;
//PST
int rng;
struct PST{
	vector<int> root,L,R,tree;
	int pv = 0, init = 0;
	PST(int n = N,int r = inf + 1) {
		root.resize(n+1);
        rng = r;
		build();
	}
	void build(int id=0,int s=0,int e=rng){
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
	int upd_new(int p,int v,int id,int s,int e){
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
	void upd_root2(int id1,int id2,int p,int v,int s=0,int e=rng){
		root[id1] = upd_new(p,v,root[id2],s,e);
	}
	void upd_root(int id,int p,int v,int s=0,int e=rng){
		upd_root2(id,id-1,p,v,s,e);
	}
    int chg(int k){
        assert(0<=k && k<root.size());
        return root[k];
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
		if(k<=Lval) return qry_Kth(k,L[idL],L[idR],s,m);
		else return qry_Kth(k-Lval,R[idL],R[idR],m,e);
	}
};
