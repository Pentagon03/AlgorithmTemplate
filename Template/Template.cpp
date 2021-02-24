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

#define V(X) vector<X>
#define pb push_back
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end() 
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)

#define nl '\n'
#define sp ' '
#define prt(x) cerr<<#x<<": "<<x<<nl
void dbg(string s = "STILL WORKING"){puts(s.c_str());}

template<typename T> T get_random_int(T l,T r) {
	static random_device rd;
	return uniform_int_distribution<T>(l,r)(rd);
}

#define FASTIO 1
#if FASTIO
namespace in{
    const int SIZ=1<<20;
	char buf[SIZ],*p=buf+SIZ;
	inline bool isblank(char c){return c=='\n'||c==' '||c=='\t'||c=='\r';}
	inline char read(){
		if(p==buf+SIZ) fread(buf,1,SIZ,stdin), p=buf;
		return *p++;
	}
    template<typename T=int>
	inline T geti(){
		char c; do c=read(); while(isblank(c));
		T res=0; bool f=1;
		if(c=='-') f=0, c=read();
		while(isdigit(c)) res=res*10+(c&15), c=read();
		return f?res:-res;
	}
	inline void scan(string&s){
		s.clear(); char c; do c=read(); while(isblank(c));
		while(!isblank(c)) s.push_back(c), c=read();
	}
    template<typename T> inline void scan(T&n){ n = geti<T>(); }
    template<typename T, typename... Args> inline void scan(T&n, Args&...args){
        scan(n); scan(args...);
    }
}
namespace out{
    const int SIZ=1<<20;
	char buf[SIZ],*p=buf,tmp[21];
	inline void flush(){fwrite(buf,1,p-buf,stdout);}
	inline void write(char c){
		if(p==buf+SIZ) flush(), p=buf;
		*p++=c;
	}
	inline void write(const string&s,char sep = '\n'){
		flush(); fwrite(s.c_str(),1,s.length(),stdout); 
		if(sep) write(sep);
	}
    template<typename T>
	inline void write(T ans,char sep = '\n'){
		if(ans<0) write('-'),ans*=-1;
		int cnt=0;
	    do tmp[cnt++]=(ans%10)|48, ans/=10; while(ans>0);
	    for(;cnt--;) write(tmp[cnt]);
	    if(sep) write(sep);
	}
	template<typename T>
	inline void write(const vector<T>&v){
		for(auto k:v) write(k,' ');
		write('\n');
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

int TC = 1;
bool getTC = 0, printTC = 0, useDouble = 0;
const bool startup = [](){
	// #define ONLINE_JUDGE
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(0); 
	#endif
	if(getTC) cin>>TC;
	if(useDouble) cout<<fixed<<setprecision(12);
	return true;
}();

const int N = 1e5+5, inf = 1e9, mod = 1e9+7;
// int n;
// vector<int> v(3);
// void input(){
// 	cin>>n; v.assign(n,0);
// 	rep(i,n) cin>>v[i];
// }
void solve(){
	int n; scan(n);
	V(int) v(n);
	rep(i,n) cin>>v[i];
	write(v);
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

