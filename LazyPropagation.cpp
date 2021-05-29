#include<bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T=ll>
struct Seg{
    int st=1; vector<T> tree,lazy;
    Seg(int k=1){
        while(st<k) st<<=1;
        tree=lazy=vector<T>(st*2);
    }
    inline T op(T a,T b){return a+b;}
    T& elem(int k){return tree[st+k];}
    void build(){for(int i=st-1;i>0;i--) tree[i] = op(tree[i<<1], tree[i<<1|1]);}
    T init(int nd,int s,int e,vector<T>&v){
        if(s==e) return tree[nd] = v[s-1];
        return tree[nd] = op(init(nd<<1,s,s+e>>1,v),init(nd<<1|1,s+e+2>>1,e,v));
    }
    void apply(int nd,int s,int e,T v){
        lazy[nd] += v; tree[nd] += (e-s+1)*v;
    }
    void push(int nd,int s,int e){
        if(s==e) return;
        apply(nd<<1,s,s+e>>1,lazy[nd]); apply(nd<<1|1,s+e+2>>1,e,lazy[nd]);
        lazy[nd] = 0;
    }
    //md=0 : range update, md=1: range sum
    T qry(int nd,int s,int e,int l,int r,int md,T v=0){
        T res=0;
        if(l <= s && e <= r){
            if(md==0) apply(nd,s,e,v);
            else res = tree[nd];
        }else if(s <= r && l <= e){
            push(nd,s,e);
            T L = qry(nd<<1,s,s+e>>1,l,r,md,v), R = qry(nd<<1|1,s+e+2>>1,e,l,r,md,v);
            if(md==0) tree[nd] = op(L,R);
            else res = op(L,R);
        }
        return md==0?tree[nd]:res;
    }
};

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n,m,k;
    cin>>n>>m>>k; m+=k;
    Seg ST(n);  vector<ll> v(n);
    for(int i=0;i<n;i++) cin>>v[i];
    ST.init(1,1,n,v);
    while(m--){
        int sel,a,b; ll c; cin>>sel>>a>>b;
        if(sel==1) cin>>c, ST.qry(1,1,n,a,b,0,c);
		else cout<<ST.qry(1,1,n,a,b,1)<<'\n';
	}
	return 0;
}
