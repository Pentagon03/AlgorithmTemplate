//Don't use FASTIO when u are handling real numbers
#define FASTIO 1
#if FASTIO
namespace in{
    const int SIZ=1<<20;
	char buf[SIZ],*p=buf+SIZ;
	inline bool isblank(char c){return c=='\n'||c==' '||c=='\t'||c=='\r'||c==0;}
	inline char read(){
		if(p==buf+SIZ) fread(buf,1,SIZ,stdin), p=buf;
		return *p++;
	}
	inline void scan(char&c){do c=read(); while(isblank(c));}
    template<typename T=int>
	inline T geti(){
		char c; scan(c);
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
	inline void flush(){fwrite(buf,1,p-buf,stdout); p=buf;}
	inline void write(char c){
		if(p==buf+SIZ) flush();
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
