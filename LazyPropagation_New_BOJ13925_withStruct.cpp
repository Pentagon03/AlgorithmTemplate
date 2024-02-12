/*Solution
https://acmicpc.net/problem/13925

Better Implementation 

Implementation Reference
brandonzhang: https://www.acmicpc.net/source/35901228

another interesting..
dohoon: https://www.acmicpc.net/source/55687464
*/

#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define sp ' '
#define dbg(i) cerr<<#i<<sp<<i<<endl
#define all(v) begin(v),end(v)
// #define int long long
using ll = long long;
using pii = pair<int,int>;
int cur_tc;
constexpr int N = 1e5 + 7, inf = (int)1e9 + 7, mod = (int)1e9 + 7;
constexpr ll linf = (ll)4e18 + 7;
template<typename T>
struct lazyseg{
    struct node{
        T sum = 0, lzmul = 1, lzadd = 0;
        void apply(node const&p, int l,int r){
            auto m = p.lzmul;
            if(m != 1){
                sum *= m; sum %= mod;
                lzadd *= m; lzadd %= mod;
                lzmul *= m; lzmul %= mod;
            }
            auto a = p.lzadd;
            if(a != 0){
                sum += a * (r-l+1) % mod; sum %= mod;
                lzadd += a; lzadd %= mod;
            }
        }
    };
    vector<node> t;
    int SZ;
    lazyseg(int n = 1){
        SZ = 1;
        while(SZ < n) SZ <<= 1;
        t.resize(SZ << 1);
    }
    void build(){
        for(int i=SZ-1;i>=1;i--)
            pull(i);
    }
    void push(int i,int l,int r){
        if(i < SZ){
            int m = (l+r) / 2;
            t[2*i].apply(t[i], l, m);
            t[2*i+1].apply(t[i],m+1,r);
            t[i] = {t[i].sum,1,0};
        }
    }
    void pull(int i){
        if(i < SZ){
            t[i].sum = (t[2*i].sum + t[2*i+1].sum) % mod;
        }
    }
    int x, y; node v;
    
    void _upd(int i,int l,int r){
        if(x > r or y < l) return;
        if(x <= l and r <= y){
            t[i].apply(v, l, r);
            return;
        }
        push(i, l, r);
        int m = (l+r) / 2;
        _upd(2*i, l, m); _upd(2*i+1, m+1, r);
        pull(i);
    }
    void upd(int _x,int _y,node const&_v){
        x = _x; y =_y; v = _v;
        _upd(1,0,SZ-1);
    }

    T _qry(int i,int l,int r){
        if(x > r or y < l) return 0;
        if(x <= l and r <= y) return t[i].sum;
        push(i, l, r);
        int m = (l+r) / 2;
        return (_qry(2*i,l,m) + _qry(2*i+1,m+1,r)) % mod;
    }
    T qry(int _x,int _y){
        x = _x; y = _y;
        return _qry(1, 0, SZ-1);
    }
};
void solve(){
    int n; cin>>n;

    lazyseg<ll> f(n);
    for(int i=0;i<n;i++)
        cin>>f.t[f.SZ+i].sum;
    f.build();

    int q; cin>>q;
    while(q--){
        int k; cin>>k;
        if(k<=3){
            int x,y,v; cin>>x>>y>>v;
            --x; --y;
            if(k==1) f.upd(x, y, {0,1,v});
            else if(k==2) f.upd(x, y, {0,v,0});
            else f.upd(x, y, {0,0,v});
        }else{
            int x,y; cin>>x>>y;
            --x; --y;
            cout<< f.qry(x, y) << nl;
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int tc = 1;
    // cin >> tc;
    for(cur_tc=1;cur_tc<=tc;++cur_tc) solve();
    return 0;
}
