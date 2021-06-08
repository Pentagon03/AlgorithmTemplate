//Don't use FASTIO when useDouble==1 or printTC==1
#define FASTIO 1
#if FASTIO
namespace IN{
	const int SIZ=1<<20;
	char buf[SIZ+1],*p=buf+SIZ;
	inline bool isblank(char c){return c=='\n'||c==' '||c=='\t'||c=='\r'||c==0;}
	inline char read(){
		if(p==buf+SIZ) buf[fread(buf,1,SIZ,stdin)]=0, p=buf;
		return *p++;
	}
	inline void scan(char&c){do c=read(); while(isblank(c));}
	template<typename T=int>
	inline T geti(){
		char c; scan(c);
		T res=0; bool f=1;
		if(c=='-') f=0, c=read();
		while(c>='0'&&c<='9') res=res*10+(c&15), c=read();
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
}
using namespace IN;
namespace OUT{
	const int SIZ=1<<20;
	char buf[SIZ+1],*p=buf,tmp[21];
	inline void flush(){fwrite(buf,1,p-buf,stdout); p=buf;}
	inline void mark(char c){
		if(p==buf+SIZ) flush();
		*p++=c;
	}
	inline void mark(const char*s,char sep = '\n'){
		for(int i=0;s[i];i++) mark(s[i]);
		if(sep) mark(sep);
	}
	inline void mark(const string&s,char sep = '\n'){
		for(char c:s) mark(c);
		if(sep) mark(sep);
	}
	template<typename T> inline void mark(T ans,char sep = '\n'){
		if(ans<0) mark('-'),ans*=-1;
		int cnt=0;
		do tmp[cnt++]=(ans%10)|48, ans/=10; while(ans>0);
		for(;cnt--;) mark(tmp[cnt]);
		if(sep) mark(sep);
	}
	template<typename T> inline void mark(const vector<T>&v){
		for(auto k:v) mark(k,' ');
		mark('\n');
	}
	struct ff{ ~ff(){flush();}}flu;
}
using namespace OUT;
#else
template<typename T=int> inline T geti(){T k; cin>>k; return k;}
template<typename T> inline void scan(T&n){cin>>n;}
template<typename T, typename... Args> inline void scan(T&n, Args&...args){
scan(n); scan(args...);
}
template<typename T>
inline void mark(T ans,char sep = '\n'){cout<<ans<<sep;}
#endif
