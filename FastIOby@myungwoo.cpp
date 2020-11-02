//전명우님의 Fast Integer IO
//https://blog.myungwoo.kr/130
template<typename T> inline void read(T &x){
    char c=getchar();bool f=0;x=0;
    while(!isdigit(c)) f|=c=='-',c=getchar();
    while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
    if(f) x=-x;
}
template<typename T, typename... Args> inline void read(T &x, Args& ...args){
    read(x); read(args...);
}
template<typename T> inline void write(T x){
    if(x<0) putchar('-'),write(-x);
    else{if(x>9) write(x/10);putchar('0'+x%10);}
}
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
