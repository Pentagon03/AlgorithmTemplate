// ██████╗░███████╗███╗░░██╗████████╗░█████╗░░██████╗░░█████╗░███╗░░██╗
// ██╔══██╗██╔════╝████╗░██║╚══██╔══╝██╔══██╗██╔════╝░██╔══██╗████╗░██║
// ██████╔╝█████╗░░██╔██╗██║░░░██║░░░███████║██║░░██╗░██║░░██║██╔██╗██║
// ██╔═══╝░██╔══╝░░██║╚████║░░░██║░░░██╔══██║██║░░╚██╗██║░░██║██║╚████║
// ██║░░░░░███████╗██║░╚███║░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝██║░╚███║
// ╚═╝░░░░░╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░╚═╝░░╚══╝
// Problem : 
// bit.ly/pentagon03 

#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
#define fi first
#define se second

// using C = double;
// using P = pair<C,C>;
// const double eps = 1e-9;
// #define X first
// #define Y second

#define V(X) vector<X>
#define pb push_back
#define eb emplace_back
#define ep emplace
#define all(v) (v).begin(),(v).end() 
#define sz(v) ((int)(v).size())
#define compress(v) sort(all(v)),v.erase(unique(all(v)),v.end())

#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define repr(i,a,b) for(int i=(a);i<=(b);i++)
#define repd(i,b,a) for(int i=(b);i>=(a);i--)

#define nl '\n'
#define sp ' '
#define yes(T) cout<<(T?"YES\n":"NO\n")
#define prt(x) cerr<<#x<<": "<<x<<nl
#define pprt(x) cout<<(x)
void dbg(string s = "STILL WORKING"){puts(s.c_str());}

int TC = 1;
bool getTC = 0, printTC = 0, useDouble = 0, fileInput = 0, fileOutput = 0;
#define FASTIO 1
const bool startup = [](){
	//#define ONLINE_JUDGE
	#ifdef ONLINE_JUDGE
	if(!FASTIO) ios::sync_with_stdio(!cin.tie(0)); 
	#endif
	if(fileInput) freopen("input.txt","r",stdin);
	if(fileOutput) freopen("output.txt", "w", stdout);
	if(getTC) cin>>TC;
	if(useDouble) cout<<fixed<<setprecision(12);
	return true;
}();

#if FASTIO
namespace in{
    const int SIZ=1<<20;
	char buf[SIZ];
	int idx=0,ridx=0;
	inline char read(){
		if(idx==ridx)
			idx=buf[ridx=fread(buf,1,SIZ,stdin)]=0;
		return buf[idx++];
	}
    template<typename T=int>
	inline T geti(){
		T sum=0; bool f=1;
		char c=read();
		while(c<=32) c=read();
		if(c=='-') f=0,c=read();
		while(c>=48&&c<=57)
			sum=sum*10+(c&15), c=read();
		return f?sum:-sum;
	}
    template<typename T> inline void scan(T&n){ n = geti<T>(); }
    template<typename T, typename... Args> inline void scan(T&n, Args&...args){
        scan(n); scan(args...);
    }
}
namespace out{
    const int SIZ2=1<<20;
	char buf[SIZ2],tmp[21];
	int idx=0;
	inline void flush(){fwrite(buf,1,idx,stdout);}
	inline void write(char c){
		if(idx==SIZ2)
			flush(), idx=0;
		buf[idx++]=c;
	}
    template<typename T>
	inline void mark(T ans,char sep = '\n'){
		if(ans<0) write('-'),ans*=-1;
		int cnt=0;
	    do tmp[cnt++]=(ans%10)|48, ans/=10; while(ans>0);
	    for(;cnt--;) write(tmp[cnt]);
	    write(sep);
	}
    struct ff{ ~ff(){flush();}}flu;
}
using namespace in;
using namespace out;
#else
template<typename T=int> inline T geti(){T k; cin>>k; return k;}
template<typename T> inline void scan(T&n){cin>>n;}
template<typename T, typename... Args> inline void scan(T&n, Args&...args){
    scan(n); scan(args...);
}
template<typename T>
inline void mark(T ans,char sep = '\n'){cout<<ans<<sep;}
#endif

// int n;
// vector<int> v(3);
// void input(){
// 	cin>>n; v.assign(n,0);
// 	rep(i,n) cin>>v[i];
// }

const int N = 2e5+1, inf = 1e9, mod = 998244353;

typedef complex<double> base;
#define M_PI 3.14159265358979323846
void fft(vector <base> &a, bool invert)
{
    int n = sz(a);
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
        double ang = 2*M_PI/len*(invert?-1:1);
        base wlen(cos(ang),sin(ang));
        for (int i=0;i<n;i+=len){
            base w(1);
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }
    if (invert){
        for (int i=0;i<n;i++) a[i] /= n;
    }
}
 
void multiply(const vector<int> &a,const vector<int> &b,vector<int> &res)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
    while (n < max(sz(a),sz(b))) n <<= 1;
    //다항식을 제곱하는 경우 2*n까지 계수가 가능하다
    n <<= 1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    res.resize(n);
    for (int i=0;i<n;i++) res[i] = int(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
}

//출처: https://blog.myungwoo.kr/54 [PS 이야기]

void solve(){
    int n; scan(n);
    vector<int> A(N),C;
    A[0] = 1;
    rep(i,n) A[geti()] = 1;
    multiply(A,A,C);
    int m, ans = 0; scan(m);
    rep(i,m) if(C[geti()]) ++ans;
    mark(ans);
}

// did you initialize properly?
// any Corner cases?
// any long long needed?

int main(){
	rep1(tc,TC){
		if(printTC) cout<<"Case #"<<tc<<": ";
		solve();
	}
	return 0;
}


// Solution
/*



*/

