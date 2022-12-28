// Just use as if we use cin.
// Or...
//int a=3; string b = "hello"; _in.scan(a,b);

#define FASTIO 1
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
        inline void mark(char c){
            if(p==buf+SIZ) flush();
            *p++=c;
        }
        inline void mark(const char*s){
            for(int i=0;s[i];i++) mark(s[i]);
        }
        inline void mark(const string&s){
            for(char c:s) mark(c);
        }
        template<typename T> inline void mark(const vector<T>&v){
            for(auto k:v) mark(k), mark(' ');
        }
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
