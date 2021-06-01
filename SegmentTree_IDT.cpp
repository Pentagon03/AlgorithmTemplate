//0 based
template<typename T=ll>
struct Seg{
    int n; vector<T> t;
    Seg(int k=1):n(k){t.assign(2*n,T());}
    inline T op(T a,T b){return a+b;}
    void init(vector<T>&v){
        n = v.size(); t.assign(2*n,T());
        for(int i=0;i<n;i++) t[n+i]=v[i];
        for(int i=n-1;i>=1;i--) t[i]=op(t[i<<1],t[i<<1|1]);
    }
    void upd(int pos,T v){
        for(t[pos+=n]=v;pos>>=1;) t[pos]=op(t[pos<<1],t[pos<<1|1]);
    }
    T qry(int l,int r){
        T res=T();
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1) res=op(res,t[l++]);
            if(!(r&1)) res=op(res,t[r--]); 
        }
        return res;
    }
};
