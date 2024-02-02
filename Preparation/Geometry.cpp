namespace Geometry{
    using C = double;
    const C EPS = 1e-12;
    const C PI = acos(-1);
    using T = ll;
    using P = pair<T,T>;
    #define fi first
    #define se second
    const P O = P(0,0), FAIL = P(numeric_limits<T>::max(), numeric_limits<T>::max());
    inline T inner(P a,P b){ return a.fi*b.fi + a.se*b.se;} //inner product
    inline T cross(P a,P b){ return a.fi*b.se - a.se*b.fi;} //vector product
    istream& operator>> (istream& is, P& p){ return is >> p.fi >> p.se;}
    inline P operator+(P a,P b){ return P(a.fi+b.fi, a.se+b.se);}
    inline P operator-(P a,P b){ return P(a.fi-b.fi, a.se-b.se);}
    inline P operator*(P a,T c){ return P(a.fi*c,a.se*c); }
    inline P operator*=(P &a, T c){ return a = a*c; }
    inline P operator-=(P&a,P b){ return a = a-b; }
    inline T sq(P a){return inner(a,a);}
    inline T dsq(P a,P b){return sq(b-a);}
    inline int ccw(P a,P b,P c){T val = cross(b-a,c-a); return val?(val>0?1:-1):0;}
    inline bool cmp_ang(P a,P b){
        if((a>O) ^ (b>O)) return a>b;
        if(cross(b,a) != 0) return cross(b,a) > 0;
        return sq(a) < sq(b);
    }
    struct Line{
        P s,e;
        Line(P a=O,P b=O):s(a),e(b){if(s>e) swap(s,e);}
        C length(){return sqrt(dsq(s,e));}
        bool is_on_line(P x){return !ccw(s,e,x) && s<=x && x<=e;}
        friend bool chk_inter(Line a, Line b){
            int t1 = ccw(a.s,a.e,b.s); int t2 =  ccw(a.s,a.e,b.e);
            int t3 = ccw(b.s,b.e,a.s); int t4 =  ccw(b.s,b.e,a.e);
            if(!t1 && !t2){
                // two lines are already sorted
                return a.s <= b.e && b.s <= a.e;
            }
            return t1*t2 <= 0 && t3*t4 <= 0;
        }
        friend P parrallel_inter(Line a,Line b){
            if(a.e==b.s) return a.e;
            if(b.e==a.s) return b.e;
            return FAIL;
        }
        // only works when T = double
        friend P inter(Line p,Line q){
            P a=p.s, b=p.e, c=q.s, d=q.e;
            int t1 = ccw(a,c,d) , t2 = ccw(b,c,d);
            if(t1 == 0 && t2 == 0)
                return parrallel_inter(p,q);
            b-=a; d-=c;
            C t = cross(c-a,d) / cross(b,d);
            return a + b*t;
        }
        friend C dist(Line a,P x){ return abs(cross(a.e-a.s,x-a.s))/a.length(); }
    };

    using Polygon = vector<P>;
    Polygon getCH(Polygon pg){ //Monotone Chain of polygon
        if(size(pg)<=3) return pg;
        sort(all(pg));
        Polygon up(size(pg)),dn(size(pg)); int u=0,d=0;
        for(const P&p:pg){
            while(u>1 && ccw(up[u-2],up[u-1],p)>=0) --u;
            while(d>1 && ccw(dn[d-2],dn[d-1],p)<=0) --d;
            up[u++] = dn[d++] = p;
        }
        up.resize(u); dn.resize(d);
        dn.insert(dn.end(),++up.rbegin(),--up.rend());
        return dn;
    }
    bool chk_in_naive(const Polygon&h, P p){
        // strictly inner
        int s = ccw(h[0],h[1],p);
        for(int i=1;i<size(h);i++){
            if(s * ccw(h[i], h[(i+1) % size(h)], p) <= 0) return false;
        }
        return true;
    }
}
using namespace Geometry;
