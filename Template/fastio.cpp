#define FASTIO 1
/**
 * https://github.com/Pentagon03/AlgorithmTemplate/blob/main/Template/fastio.cpp
 * Just use as if we use cin, cout. 
 * Or manually. ex) int a=3; string b = "hello"; _in.scan(a,b); int z = _in.geti();
 * Special function: vector, pair input/output => vector<int> v(3); cin>>v; // Works!
 * Default floating point length is 6
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
