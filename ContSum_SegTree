//https://www.acmicpc.net/problem/16993
#pragma GCC optimize("Ofast")
//Always Do Your Best Ku!
#include<bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v).size())
#define nl '\n'
#define sp ' '
using ll = long long;
using pii = pair<int,int>;
const int inf = 1e9;
#define dbg(X) cerr<<#X<<'='<<X<<nl
#define GET_TC 0

template<typename T = ll,const T inf = T(1e18)>
struct SegCon{
    struct Node{
        T mx, rmx, lmx, sum;
        Node(){mx = rmx = lmx = -inf; sum = 0;}
        Node(T a,T b,T c,T d):mx(a),rmx(b),lmx(c),sum(d){}
    }base;
    vector<Node> tree; int b=1;
    SegCon(int n=1){
        while(b<n) b <<= 1;
        tree.resize(b<<1);
    }
    Node f(Node a,Node b){
        Node res;
        res.sum = a.sum + b.sum;
        res.lmx = max(a.lmx,a.sum+b.lmx);
        res.rmx = max(b.rmx,b.sum+a.rmx);
        res.mx = max({a.mx,b.mx,a.rmx+b.lmx});
        return res;
    }
    Node init(int nd,int s,int e,vector<T>&v){
        if(s+1==e)
            return tree[nd] = Node(v[s],v[s],v[s],v[s]);
        int m = s + e >> 1;
        return tree[nd] = f(init(nd<<1,s,m,v),init(nd<<1|1,m,e,v));
    } void init(vector<T>&v){ v.resize(b); init(1,0,b,v);}

    void upd(int p,int v){
        for(tree[p|=b]={v,v,v,v};p>1;p>>=1)
            tree[p>>1] = f(tree[p],tree[p^1]);
    } 

    Node query(int nd,int s,int e,int l,int r){
        if(e<=l || r<=s) return base;
        if(l<=s && e<=r) return tree[nd];
        int m = s + e >> 1;
        return f(query(nd<<1,s,m,l,r),query(nd<<1|1,m,e,l,r));
    } T query(int l,int r){return query(1,0,b,l,r).mx;}
};

void solve(int TC){
    int n; cin>>n;
    SegCon tree(n); 
    vector<ll> v(n); for(int i=0;i<n;i++) cin>>v[i];
    tree.init(v);
    int Q; cin>>Q;
    while(Q--){
        int a,b; cin>>a>>b;
        cout<<tree.query(--a,b)<<nl;
    }
}

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int T = 1; if(GET_TC) cin >> T;
    for(int i=1;i<=T;i++) solve(i);
}
