struct Node{
    int mx, mn;
    Node():mx(-inf),mn(inf){}
    Node(int k){mx=mn=k;}
};
Node operator+(Node a,Node b){
    Node res;
    res.mx = max(a.mx, b.mx);
    res.mn = min(a.mn, b.mn);
    return res;
}
template<typename T=ll>
struct Seg{
    int n; vector<T> t;
    Seg(int k=1):n(k){t.assign(2*n,T());}
    void init(vector<T>&v){
        n = v.size(); t.assign(2*n,T());
        for(int i=0;i<n;i++) t[n+i]=v[i];
        for(int i=n-1;i>=1;i--) t[i]=t[i<<1]+t[i<<1|1];
    }
    void upd(int pos,T v){
        for(t[pos+=n]=v;pos>>=1;) t[pos]=t[pos<<1]+t[pos<<1|1];
    }
    T qry(int l,int r){
        T res=T();
        for(l+=n,r+=n;l<=r;l>>=1,r>>=1){
            if(l&1) res=t[l++]+res;
            if(!(r&1)) res=res+t[r--];
        }
        return res;
    }
};
