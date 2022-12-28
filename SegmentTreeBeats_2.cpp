//Reference Problem: https://www.acmicpc.net/problem/19455
#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define sp ' '
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define all(v) v.begin(),v.end()
#define sz(v) ((int)(v).size())
#ifndef ONLINE_JUDGE
#define dbg(x) cerr<<#x<<": "<<x<<nl;
#else
#define dbg(x) NULL;
#endif 
#define IV(v,n) vector<int> v(n); for(auto&k:v) cin>>k
using ll = long long;
using pii = pair<int,int>;

// Just use as if we use cin.
// Or...
//int a=3; string b = "hello"; _in.scan(a,b);

#define FASTIO 1
#if FASTIO
//https://github.com/Pentagon03/AlgorithmTemplate/blob/main/Template/fastio.cpp
constexpr int SIZ = 1<<18;
class _IN{
    private:
	    char buf[SIZ+1],*p=buf+SIZ;
    public:
        inline bool isblank(char c){return c=='\n'||c==' '||c=='\t'||c=='\r'||c==0;}
        inline char read(){
            if(p==buf+SIZ) buf[fread(buf,1,SIZ,stdin)]=0, p=buf;
            return *p++;
        }
        inline void scan(char&c){do c=read(); while(isblank(c));}
        template<typename T=int> inline T geti(){
            char c; scan(c);
            T res=0; bool f=1;
            if(c=='-') f=0, c=read();
            while(c>='0'&& c<='9') res=res*10+(c&15), c=read();
            return f?res:-res;
        }
        inline void scan(string&s){
            s.clear(); char c; scan(c);
            while(!isblank(c)) s.push_back(c), c=read();
        }
        template<typename T> inline void scan(T&n){ n = geti<T>(); }
        template<typename T, typename... Args> inline void scan(T&n, Args&...args){
            scan(n); scan(args...);
        }
} _in;
class _OUT{
    private:
	    char buf[SIZ+1],*p=buf, tmp[21];
    public:
        inline void flush(){fwrite(buf,1,p-buf,stdout); p=buf;}
        inline void mark(char c){{if(p==buf+SIZ) flush();} *p++=c; }
        inline void mark(const char*s){for(int i=0;s[i];i++) mark(s[i]); }
        inline void mark(const string&s){for(char c:s) mark(c);}
        template<typename T> inline void mark(const vector<T>&v){for(auto k:v) mark(k), mark(' ');}
        template<typename T> inline void mark(T ans){
            if(ans<0) mark('-'),ans*=-1;
            int cnt=0;
            do tmp[cnt++]=(ans%10)|48, ans/=10; while(ans>0);
            for(;cnt--;) mark(tmp[cnt]);
        }
        ~_OUT(){flush();}
} _out;
template<typename T> _IN& operator>> (_IN&in, T&i){in.scan(i); return in; }
template<typename T> _OUT& operator<< (_OUT&out, T i){out.mark(i); return out; }
#define cin _in
#define cout _out
#define istream IN
#define ostream OUT
#endif


/**
 * Segment Tree Beats
 * andq는 1 비트는 무쓸모, 0비트만 효력 있음
 * orq는 0 비트는 무쓸보, 1비트만 효력 있음
*/


struct Node{
    ll mn, onv, offv, onlz, offlz;
    Node(ll v=0): mn(v), onv(v), offv(~v), onlz(0), offlz(0){}
    void down(Node&n){
        //onlz와 offlz는 겹치지 않는 것이 보장됨
        n.mn |= onlz;
        n.mn &= ~offlz;
        n.onv |= onlz;
        n.onv &= ~offlz;
        n.offv &= ~onlz;
        n.offv |= offlz;
        n.onlz |= onlz;
        n.onlz &= ~offlz;
        n.offlz &= ~onlz;
        n.offlz |= offlz;
    }
};
inline const Node operator +(Node a, Node b){
    Node x;
    x.mn = min(a.mn,b.mn);
    x.onv = a.onv & b.onv;
    x.offv = a.offv & b.offv;
    return x;
}

Node tr[1<<20]; int v[1<<19];
struct SegBeats{
    void init(int nd,int s,int e){
        if(s==e) tr[nd] = Node(v[s]);
        else{
            init(nd<<1,s,s+e>>1); init(nd<<1|1,s+e+2>>1,e);
            tr[nd] = tr[nd<<1] + tr[nd<<1|1];
        }
    }
    void down(int nd, int s, int e){
        if(s==e) return;
        tr[nd].down(tr[nd<<1]);
        tr[nd].down(tr[nd<<1|1]);
        tr[nd].onlz = tr[nd].offlz = 0;
    }
    void onq(int nd,int s,int e,int l,int r,ll x){
        //break condition (strengthend)
        if(s > r || e < l) return;
        x -= tr[nd].onv & x; //이미 켜져 있는건 안 켜도 됨
        if(!x) return;
        //tag condition (weakened)
        int canOn = tr[nd].offv & x;
        if(l <= s && e <= r && canOn == x){
            tr[nd].mn |= canOn;
            tr[nd].onv |= canOn;
            tr[nd].offv &= ~canOn;
            tr[nd].onlz |= canOn;
            tr[nd].offlz &= ~canOn;
            x -= canOn;
        }
        if(x==0) return;
        down(nd,s,e);
        onq(nd<<1,s,s+e>>1,l,r,x); onq(nd<<1|1,s+e+2>>1,e,l,r,x);
        tr[nd] = tr[nd<<1]+tr[nd<<1|1];
    }
    void offq(int nd,int s,int e,int l,int r,ll x){
        //break condition (strengthend)
        if(s > r || e < l) return;
        x -= tr[nd].offv & x; //이미 꺼져 있는건 안 꺼도 됨.
        if(!x) return;
        //tag condition (weakened)
        int canOff = tr[nd].onv & x;
        if(l <= s && e <= r && canOff == x){
            tr[nd].mn &= ~canOff;
            tr[nd].onv &= ~canOff;
            tr[nd].offv |= canOff;
            tr[nd].onlz &= ~canOff;
            tr[nd].offlz |= canOff;
            x -= canOff;
        }
        if(x==0) return;
        down(nd,s,e);
        offq(nd<<1,s,s+e>>1,l,r,x); offq(nd<<1|1,s+e+2>>1,e,l,r,x);
        tr[nd] = tr[nd<<1]+tr[nd<<1|1];
    }
    
    int qry(int nd,int s,int e,int l,int r){
        if(s>r||e<l) return INT32_MAX;
        if(l<=s&&e<=r) return tr[nd].mn;
        down(nd,s,e);
        int ans = min(qry(nd<<1,s,s+e>>1,l,r),qry(nd<<1|1,s+e+2>>1,e,l,r));
        tr[nd] = tr[nd<<1] + tr[nd<<1|1];
        return ans;
    }
};


void solve(){
    SegBeats f;
    int n; cin>>n;
    rep(i,n) cin>>v[i];
    f.init(1,0,n-1);
    int m; cin>>m;
    while(m--){
        char q; ll l,r,x; cin>>q>>l>>r; --l; --r;
        if(q=='?'){
            cout<<f.qry(1,0,n-1,l,r)<<nl;
        }else{
            cin>>x;
            if(q=='&'){
                f.offq(1,0,n-1,l,r,~x);
            }else{
                f.onq(1,0,n-1,l,r,x);
            }
        }
        // for(int i=0;i<n;i++)
        //     cout<<f.qry(1,0,n-1,i,i)<<sp;
        // cout<<nl;
    }
}


int main(){
    #if !FASTIO
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
