/*Solution
https://acmicpc.net/problem/13925

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

constexpr int MOD = 1e9 + 7;
struct node{
    ll sum, lzadd, lzmul, lzset;
    node(int a=0,int b=0,int c=1,int d=0):sum(a),lzadd(b),lzmul(c),lzset(d){}
    void apply(const node&p, int l, int r){
        // [l, r]
        if(p.lzset != 0){
            sum = p.lzset * (r-l+1) % MOD;
            lzadd = 0;
            lzmul = 1;
            lzset = p.lzset;
        }
        if(p.lzmul != 1){
            sum = sum * p.lzmul % MOD;
            lzadd = lzadd * p.lzmul % MOD;
            lzmul = lzmul * p.lzmul % MOD;
        }
        if(p.lzadd != 0){
            sum += (p.lzadd) * (r-l+1) % MOD;
            sum %= MOD;
            lzadd += p.lzadd;
            lzadd %= MOD;
        }
    }
};

/*
to use multiple segs,
you must get rid of default values in the function
and manually use seg.st;
*/
int st;
struct seg{
    vector<node> t;
    // int st;
    seg(int n = (1<<17)){
        st = 1;
        while(st < n) st <<= 1;
        t.resize(st<<1);
    }
    void build(vector<node>&v){
        for(int i=0;i<size(v);i++)
            t[st+i] = v[i];
        for(int i=st-1; i>=1; i--)
            pull(i);
    }
    void push(int i, int l, int r){
        if(i < st){
            int m = (l+r) / 2;
            t[2*i].apply(t[i], l, m);
            t[2*i+1].apply(t[i],m+1,r);
            t[i] = node(t[i].sum);
        }
    }
    void pull(int i){
        t[i].sum = (t[2*i].sum + t[2*i+1].sum) % MOD;
    }
    void upd(int x,int y, const node& v, int i=1, int l=0, int r=st-1){
        if(x > r or y < l) return;
        if(x <= l and r <= y){
            t[i].apply(v, l, r);
            return;
        }
        push(i, l, r);
        int m = (l+r)/2;
        upd(x, y, v, 2*i, l, m);
        upd(x, y, v, 2*i+1, m+1, r);
        pull(i);
    }
    ll qry(int x,int y, int i=1, int l=0, int r=st-1){
        if(x > r or y < l) return 0;
        if (x <= l and r <= y) return t[i].sum;
        push(i, l, r);
        int m = (l+r)/2;
        ll ans = (qry(x, y, 2*i, l, m) + qry(x, y, 2*i+1, m+1, r))%MOD;
        return ans;
    }
};

void solve(){
    int n; cin>>n;

    seg f(n);
    vector<node> v(n);
    for(int i=0;i<n;i++)
        cin>>v[i].sum;
    f.build(v);

    
    int q; cin>>q;
    while(q--){
        int k; cin>>k;
        if(k<=3){
            int x,y,v; cin>>x>>y>>v;
            --x; --y;
            if(k==1) f.upd(x, y, node(0,v,1,0));
            else if(k==2) f.upd(x, y, node(0,0,v,0));
            else f.upd(x, y, node(0,0,1,v));
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
