#include<bits/stdc++.h>
#define all(v) v.begin(),v.end()
using namespace std;
const int N = 3e5;
using ll = long long;

//Minimum Query, Range Sum update
struct Seg{
    int n,N;
    vector<int> tree,lazy;
    void init(int k){
        n = k;
        int N = 1 << int(ceil(log2(n)))+1;
        tree.resize(N); lazy.resize(N); 
    }
    void push(int nd,int st,int en){
        tree[nd] += lazy[nd];
        if(st!=en){
            lazy[nd<<1] += lazy[nd];
            lazy[nd<<1|1] += lazy[nd];
        }
        lazy[nd] = 0;
    }
    void update(int l,int r,int val,int nd,int st,int en){
        push(nd,st,en);
        if(r<st || en<l) return;
        if(l<=st && en<=r){
            lazy[nd] += val;
            push(nd,st,en);
        }
        else{
            int md = st + en >> 1;
            update(l,r,val,nd<<1,st,md);
            update(l,r,val,nd<<1|1,md+1,en);
            tree[nd] = min(tree[nd<<1],tree[nd<<1|1]);
        }
    }
    int query(int l,int r,int nd,int st,int en){
        if(r<st||en<l) return 0;
        push(nd,st,en);
        if(l<=st && en<=r) return tree[nd];
        else{
            int md = st + en >> 1;
            return min(query(l,r,nd<<1,st,md),query(l,r,nd<<1|1,md+1,en));
        }
    }
    void upd(int l,int r,int val){
        update(l,r,val,1,1,n);
    }
    int qry(int l,int r){
        if(l>r) return 0;
        return query(l,r,1,1,n);
    }
};

void solve(){
    int n; cin>>n;
    Seg f;
    f.init(n);
}
int main(){
    ios::sync_with_stdio(!cin.tie(0));
    solve();
    return 0;
}
