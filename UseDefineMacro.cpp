//https://www.acmicpc.net/problem/15687
#define T(n) this->n=n;
#define P(f,n,l)void set_##f(int n){if(0<n&&n<=l*1000)T(n)}
#define F(n,c)int n()const{return c;}
struct Rectangle{int w,h;Rectangle(int w,int h){T(w)T(h)}F(get_width,w)F(get_height,h)P(width,w,1)P(height,h,2)F(area,w*h)F(perimeter,(w+h)*2)F(is_square,w==h)};
