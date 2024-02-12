/*Solution
https://acmicpc.net/problem/17429
Lazy + HLD
straightforward implementation    
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
constexpr int N = 5e5 + 7, inf = (int)1e9 + 7, mod = (int)1e9 + 7;
constexpr ll linf = (ll)4e18 + 7;

// no mod
template<typename T>
struct lazyseg{
    struct node{
        T sum = 0, lzmul = 1, lzadd = 0;
        void apply(node const&p, int l,int r){
            auto m = p.lzmul;
            if(m != 1){
                sum *= m;
                lzadd *= m;
                lzmul *= m;
            }
            auto a = p.lzadd;
            if(a != 0){
                sum += a * (T)(r-l+1);
                lzadd += a;
            }
        }
        friend node operator+(node const&l, node const&r){;
            return {(l.sum+r.sum), 1, 0};
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
            t[i] = t[2*i] + t[2*i+1];
    }
    void push(int i,int l,int r){
        int m = (l+r) / 2;
        t[2*i].apply(t[i], l, m);
        t[2*i+1].apply(t[i],m+1,r);
        t[i] = {t[i].sum,1,0};
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
        t[i] = t[2*i] + t[2*i+1];
    }
    void upd(int _x,int _y,node const&_v){
        x = _x; y =_y; v = _v;
        if(x > y) return;
        _upd(1,0,SZ-1);
    }

    node _qry(int i,int l,int r){
        if(x > r or y < l) return {0,1,0};
        if(x <= l and r <= y) return t[i];
        push(i, l, r);
        int m = (l+r) / 2;
        return _qry(2*i,l,m) + _qry(2*i+1,m+1,r);
    }
    T qry(int _x,int _y){
        x = _x; y = _y;
        if(x > y) return 0;
        return _qry(1, 0, SZ-1).sum;
    }
};

using uint = unsigned int;
lazyseg<uint> seg;

vector<int> g[N];

int sz[N], dep[N], par[N];
void dfs_sz(int x=1,int p=0){
    sz[x] = 1; par[x] = p;
    dep[x] = dep[p] + 1;
    for(auto&nx:g[x]){
        if(nx == p) continue;
        dfs_sz(nx, x);
        sz[x] += sz[nx];
        if(g[x].front() == p || sz[nx] > sz[g[x].front()])
            swap(nx, g[x].front());
    }
}

int pv = 0, in[N], out[N], top[N];
void dfs_hld(int x=1){
    in[x] = ++pv;
    for(auto&nx:g[x]){
        if(nx == par[x]) continue;
        top[nx] = (nx==g[x].front()?top[x]:nx);
        dfs_hld(nx);
    }
    out[x] = pv;
}

uint qry_subtree(int a,int op, uint v){
    uint ans = 0;
    auto upd = [&](int s,int e){
        if(op==1) seg.upd(s, e, {0,1,v});
        else if(op==3) seg.upd(s, e, {0,v,0});
        else if(op==5) ans += seg.qry(s, e);
    };
    upd(in[a], out[a]);
    return ans;
}

uint qry_path(int a,int b,int op, uint v){
    uint ans = 0;
    auto upd = [&](int s,int e){
        if(op==2) seg.upd(s, e, {0,1,v});
        else if(op==4) seg.upd(s, e, {0,v,0});
        else if(op==6) ans += seg.qry(s, e);
    };
    // a가 b보다 depth가 깊도록 유지
    while(top[a] != top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a,b);
        // do query on s ~ e
        upd(in[top[a]],in[a]);
        a = par[top[a]];
    }
    if(dep[a] < dep[b]) swap(a,b);
    upd(in[b],in[a]);
    return ans;
}

void solve(){
    int n, q; cin>>n>>q;
    seg = lazyseg<uint>(n+1);
    for(int i=0;i<n-1;i++){
        int a, b; cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs_sz();
    dfs_hld();
    while(q--){
        int op; cin>>op;
        if(op & 1){
            int x; uint v = 0;
            cin>>x; if(op!=5) cin>>v;
            uint ans = qry_subtree(x, op, v);
            if(op==5) cout<<ans<<nl;
        }else{
            int x,y; uint v = 0;
            cin>>x>>y; if(op!=6) cin>>v;
            uint ans = qry_path(x, y, op, v);
            if(op==6) cout<<ans<<nl;
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
