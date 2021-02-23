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
		while(isdigit(c))
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
	    if(sep) write(sep);
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
