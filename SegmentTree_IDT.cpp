#include<bits/stdc++.h>
using namespace std;
using ll = long long;

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

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n,m,k; cin>>n>>m>>k;
    vector<ll> v;
    for(int i=0;i<n;i++){
        ll k; cin>>k;
        v.push_back(k);
    }
    Seg ST(n); ST.init(v);
    m+=k;
    while(m--){
        ll a,b,c;
        cin>>a>>b>>c;
        if(a==1) ST.upd(b-1,c);
        else cout<<ST.qry(b-1,c-1)<<'\n';
    }
}
