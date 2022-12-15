#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define sp ' '
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define all(v) v.begin(),v.end()
#define sz(v) ((int)(v).size())
// #define GET(n) int n; cin>>n
#ifndef ONLINE_JUDGE
#define dbg(x) cerr<<#x<<": "<<x<<nl;
#else
#define dbg(x) NULL;
#endif 
#define IV(v,n) vector<int> v(n); for(auto&k:v) cin>>k
using ll = long long;
using pii = pair<int,int>;

#define fastio 0
#if fastio
#endif

/**
 * Segment Tree Beats
 * Fastio..?
*/


struct Node{
    ll mx, mn, sum, lz, lzd;
    Node(ll a=LONG_LONG_MIN,ll b = LONG_LONG_MAX, ll c = 0, ll d = 0, ll e = 0): mx(a), mn(b), sum(c), lz(d), lzd(e){} 
    void down(Node&n, ll l){
        if(lzd>0){
            n.mx = n.mn = mx; n.sum = mx * l;
            n.lz = 0; n.lzd = lzd;
        }else{
            n.mx += lz; n.mn += lz; n.sum += lz * l;
            n.lz += lz;
        }
    }
};
inline const Node operator +(Node a, Node b){
    return {max(a.mx,b.mx),min(a.mn,b.mn),a.sum+b.sum,0,0};
}

Node tr[1<<19];
struct SegBeats{
    // vector<Node> tr;
    //void resize(int n){int b=1;while(b<n)b<<=1; tr.assign(b<<1,Node());}
    SegBeats(int n = 1e5){/*resize(n);*/}
    void init(vector<int>&v,int n){/*resize(n);*/init(1,0,n-1,v);}
    Node init(int nd,int s,int e,vector<int>&v){
        if(s==e) return tr[nd]={v[s],v[s],v[s],0,0};
        return tr[nd] = init(nd<<1,s,s+e>>1,v)+init(nd<<1|1,s+e+2>>1,e,v);
    }
    
    void push(int nd, int s, int e){
        if(s==e) return;
        tr[nd].down(tr[nd<<1], (e-s+2)>>1);
        tr[nd].down(tr[nd<<1|1], (e-s+1)>>1);
        tr[nd].lz = tr[nd].lzd = 0;
    }
    void upd(int nd,int s,int e,int l,int r,ll x, bool f){
        //break condition (strengthend)
        if(s > r || e < l || (!f && !x)) return;
        //tag condition (weakened)
        if(l <= s && e <= r){
            if(f){
                ll fmx = floor(double(tr[nd].mx) / x), fmn = floor(double(tr[nd].mn) / x);
                if(fmx == fmn){
                    tr[nd].mx = tr[nd].mn = fmx; tr[nd].sum = fmx * (e-s+1); 
                    tr[nd].lz = 0; tr[nd].lzd = x;
                    return;
                }else if(tr[nd].mx == tr[nd].mn + 1){
                    x = fmx - tr[nd].mx;
                    f = false;
                }
            }
            if(!f){
                tr[nd].mx += x; tr[nd].mn += x; tr[nd].sum += x * (e-s+1);
                tr[nd].lz += x; 
                return;
            }
        }
        push(nd,s,e);
        upd(nd<<1,s,s+e>>1,l,r,x,f); upd(nd<<1|1,s+e+2>>1,e,l,r,x,f);
        tr[nd] = tr[nd<<1]+tr[nd<<1|1];
    }
    Node qry(int nd,int s,int e,int l,int r){
        if(s>r||e<l) return Node();
        if(l<=s&&e<=r) return tr[nd];
        push(nd,s,e);
        return qry(nd<<1,s,s+e>>1,l,r) + qry(nd<<1|1,s+e+2>>1,e,l,r);
        // tr[nd] = tr[nd<<1] + tr[nd<<1|1];
    }
};


void solve(){
    SegBeats f;
    int n,m; cin>>n>>m;
    vector<int> v(n); rep(i,n) cin>>v[i];
    f.init(v,n);
    while(m--){
        int q; ll l,r,x; cin>>q>>l>>r>>x; 
        if(q<=1){
            if(q==0) f.upd(1,0,n-1,l,r,x,false);
            else f.upd(1,0,n-1,l,r,x,true);    
        }else{
            Node z = f.qry(1,0,n-1,l,r);
            cout<< (z.mx) << nl;
        }
    }
}


int main(){
    #if !fastio
    cin.tie(0) -> sync_with_stdio(0);
    #endif
    // cout<<fixed<<setprecision(15);
    int T = 1;
    // cin >> T;
    for(int i=1; i<=T; i++){
        // cout<<"Case #"<<i<<": ";
        solve();
    }
}
