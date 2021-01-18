using ll = long long;
#define X first
#define Y second
using C = ll;
using P = pair<C,C>;
#define all(v) v.begin(),v.end()
P operator-(P a,P b){
    return P(a.X-b.X,a.Y-b.Y);
}
C cross(P a,P b){
    return a.X*b.Y-a.Y*b.X;
}
int ccw(P a,P b,P c){
    C res = cross(b-a,c-b);
    if(abs(res)==0) return 0;
    return res>0?1:-1;
}
vector<P> getCH(vector<P>&pt){
    if(pt.size()<3) return pt;
    sort(all(pt));
    vector<P> up,dn; int u=0,d=0;
    for(P&p:pt){
        while(u>1 && ccw(up[u-2],up[u-1],p)>0) --u,up.pop_back();
        while(d>1 && ccw(dn[d-2],dn[d-1],p)<0) --d,dn.pop_back();
        ++u; up.push_back(p);
        ++d; dn.push_back(p);
    }
    dn.insert(dn.end(),++up.rbegin(),--up.rend());
    return dn;
}
