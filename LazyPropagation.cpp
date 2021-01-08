#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MXN = 1<<20;
struct Seg{
    int st;
    vector<ll> tree,lazy;
    Seg(int k=MXN){
        st = 1<<int(ceil(log2(k)));
        tree=lazy=vector<ll>(st*2);
    }
    void build(){
        for(int i=st-1;i>0;i--)
            tree[i] = tree[i<<1] + tree[i<<1|1];
    }
    ll& elem(int k){
        return tree[st+k];
    }
    // [l,r)
    void apply(int nd,int s,int e,ll v){
        lazy[nd] += v;
        tree[nd] += (e-s)*v;
    }
    void push(int nd,int s,int e){
        // s + 1 < e 인 경우만 들어온다. 
        int mid = s + e >> 1;
        apply(nd<<1,s,mid,lazy[nd]); apply(nd<<1|1,mid,e,lazy[nd]);
        lazy[nd] = 0;
    }
    void upd(int l,int r,ll v){upd(l,r,v,1,0,st);}
    ll qry(int l,int r){return qry(l,r,1,0,st);}
    void upd(int l,int r,ll v,int nd,int s,int e){
        if(l >= e or s >= r) return;
        if(l <= s and e <= r){
            apply(nd,s,e,v);
            return;
        }
        push(nd,s,e);
        int mid = s + e >> 1;
        upd(l,r,v,nd<<1,s,mid); upd(l,r,v,nd<<1|1,mid,e);
        tree[nd] = tree[nd<<1] + tree[nd<<1|1];
    }
    ll qry(int l,int r,int nd,int s,int e){
        if(l >= e or r <= s) return 0;
        if(l <= s and e <= r) return tree[nd];
        push(nd,s,e);
        int mid = s + e >> 1;
        return qry(l,r,nd<<1,s,mid)+qry(l,r,nd<<1|1,mid,e);
    }
};
int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n,m,k;
    cin>>n>>m>>k; m+=k;
    Seg ST(n); 
	for (int i=0;i<n;i++)
        cin>>ST.elem(i);
    ST.build();
    while(m--){
        int sel,a,b; ll c; cin>>sel>>a>>b; --a;
        if(sel==1)
            cin>>c, ST.upd(a,b,c);
		else
            cout<<ST.qry(a,b)<<'\n';
	}
	return 0;
}
