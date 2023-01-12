//Reference: https://www.acmicpc.net/problem/4225
//출제자의 코드를 추측해가면서 int, ll 자료형을 정해야 한다....

#pragma GCC optimize("Ofast,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define sp ' '

#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define all(v) v.begin(),v.end()
#define sz(v) ((int)(v).size())
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define IV(v,n) vector<int> v(n); for(auto&k:v) cin>>k
using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;

#ifndef ONLINE_JUDGE
#define dbg(x) cerr<<#x<<": "<<x<<nl;
#else
#define dbg(x) NULL;
#endif 

#define FASTIO 0
/**
 * https://github.com/Pentagon03/AlgorithmTemplate/blob/main/Template/fastio.cpp
 * Just use as if we use cin, cout. 
 * Or manually. ex) int a=3; string b = "hello"; _in.scan(a,b); int z = _in.geti();
 * Special function: vector, pair input/output => vector<int> v(3); cin>>v; // Works!
 */
#if FASTIO
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
        inline void scan(string&s){
            s.clear(); char c; scan(c);
            while(!isblank(c)) s.push_back(c), c=read();
        }
        inline void scan(float&f){string t; scan(t); f=stof(t);}
        inline void scan(double&f){string t; scan(t); f=stod(t);}
        inline void scan(long double&f){string t; scan(t); f=stold(t);}
        template<typename T=int> inline T geti(){
            char c; scan(c);
            T res=0; bool f=1;
            if(c=='-') f=0, c=read();
            while(c>='0'&& c<='9') res=res*10+(c&15), c=read();
            return f?res:-res;
        }
        template<typename T1,typename T2> inline void scan(pair<T1,T2>&p){scan(p.first);scan(p.second);}
        template<typename T> inline void scan(T&n){ n = geti<T>(); }
        template<typename T> inline void scan(vector<T>&v){for(auto&k:v) scan(k);}
        template<typename T, typename... Args> inline void scan(T&n, Args&...args){
            scan(n); scan(args...);
        }
} _in;
class _OUT{
    private:
	    char buf[SIZ+1],*p=buf, tmp[21];
    public:
        inline void flush(){fwrite(buf,1,p-buf,stdout); p=buf;}
        inline void mark(const char c){{if(p==buf+SIZ) flush();} *p++=c; }
        inline void mark(const char*s){for(int i=0;s[i];i++) mark(s[i]); }
        inline void mark(const string&s){for(char c:s) mark(c);}
        inline void mark(const float f){mark(to_string(f));}
        inline void mark(const double f){mark(to_string(f));}
        inline void mark(const long double f){mark(to_string(f));}
        template<typename T> inline void mark(const vector<T>&v){for(auto k:v) mark(k), mark(' ');}
        template<typename T1,typename T2> inline void mark(const pair<T1,T2>&p){mark(p.first); mark(' '); mark(p.second);}
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
#else
template<typename T1,typename T2> istream& operator>> (istream&in, pair<T1,T2>&p){ in>>p.first>>p.second; return in; }
template<typename T> istream& operator>> (istream&in, vector<T>&v){for(auto&k:v) in>>k; return in; }
template<typename T1,typename T2> ostream& operator<< (ostream&out, pair<T1,T2>&p){out<<p.first<<' '<<p.second; return out; }
template<typename T> ostream& operator<< (ostream&out, vector<T> v){for(auto k:v) out<<k<<' '; return out; }
#endif


constexpr int N = 2e6+5, mod = 1e9+7, inf = 1e9;

using C = double;
const C EPS = 1e-12;
const C PI = acos(-1);

using P = pii;
const P O = P(0,0);
inline P operator*(P a,int c){ return P(a.fi*c,a.se*c); }
inline ll operator*(P a,P b){ return ll(a.fi)*b.fi+ll(a.se)*b.se;}
inline ll operator/(P a,P b){ return ll(a.fi)*b.se-ll(a.se)*b.fi;}
inline P operator-(P a,P b){ return P(a.fi-b.fi, a.se-b.se);}
inline P operator*=(P&a,int c){ return a = a*c; }
inline P operator-=(P&a,P b){ return a = a-b; }
inline ll sq(P a){return ll(a.fi)*a.fi+ll(a.se)*a.se;}
inline ll dsq(P a,P b){return sq(b-a);}
inline int ccw(P a,P b,P c){ll val = (b-a)/(c-a); return val?(val>0?1:-1):0;}
inline bool cmp_ang(P a,P b){
    if((a>O) ^ (b>O)) return a>b;
    if(b/a != 0) return b/a > 0;
    return sq(a) < sq(b);
}
struct Line{
    P s,e;
    Line(P a=O,P b=O):s(a),e(b){if(s>e) swap(s,e);}
    C length(){return sqrt(dsq(s,e));}
    bool is_on_line(P x){return !ccw(s,e,x) && min(s,e)<=x && x<=max(s,e);}
    friend bool inter(Line a, Line b){
        int t1 = ccw(a.s,a.e,b.s); int t2 =  ccw(a.s,a.e,b.e);
        int t3 = ccw(b.s,b.e,a.s); int t4 =  ccw(b.s,b.e,a.e);
        if(!t1 && !t2){
            // two lines are already sorted
            return a.s <= b.e && b.s <= a.e;
        }
        return t1*t2 <= 0 && t3*t4 <= 0;
    }
    friend C dist(Line a,P x){ return abs((a.e-a.s)/(x-a.s))/a.length(); }
};
vector<P> getCH(vector<P>&pg){ //Monotone Chain of polygon
    if(sz(pg)<=3) return pg;
    sort(all(pg));
    vector<P> up(sz(pg)),dn(sz(pg)); int u=0,d=0;
    for(P&p:pg){
        while(u>1 && ccw(up[u-2],up[u-1],p)>=0) --u;
        while(d>1 && ccw(dn[d-2],dn[d-1],p)<=0) --d;
        up[u++] = dn[d++] = p;
    }
    up.resize(u); dn.resize(d);
    dn.insert(dn.end(),++up.rbegin(),--up.rend());
    return dn;
}

void solve(){
    int n;
    int tc = 0;
    while(cin>>n && n){
        vector<P> v(n); cin>>v;
        v = getCH(v);
        n = sz(v);
        C ans = 1e18;
        for(int i=0;i<n;i++){
            Line t(v[i],v[(i+1)%n]);
            C mx = 0;
            for(int j=0;j<n;j++){
                mx = max(mx, dist(t,v[j]));
            }
            ans = min(ans,mx);
        }
        cout<<"Case "<<++tc<<": "<<ceil(100*ans)/100<<nl;
    }
}


int main(){
    #if !FASTIO
    cin.tie(0) -> sync_with_stdio(0);
    cout<<fixed<<setprecision(2);
    #endif
    int T = 1;
    // cin >> T;
    for(int i=1; i<=T; i++){
        // cout<<"Case #"<<i<<": ";
        solve();
    }
}
