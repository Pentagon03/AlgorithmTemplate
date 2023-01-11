// https://www.acmicpc.net/problem/6990
#pragma GCC optimize("O3,fast-math")
#include<bits/stdc++.h>
using namespace std;
typedef double C;
const C eps = 1e-4;
inline bool same(C a,C b){return abs(a-b)<eps;}
typedef complex<C> P;
#define X real()
#define Y imag()
C dist(P a){return abs(a);}
C cross(P a,P b){return (conj(a)*b).Y;}
int ccw(P a,P b,P c){
	C res = cross(b-a,c-a);
	return !same(res,0)?(res>0?1:-1):0;
}
bool operator<(const P&a,const P&b){
	C x1=a.X,x2=b.X;
	return !same(x1,x2)?x1<x2:a.Y<b.Y;
}
struct Line{
	P st,en;
	Line(P a,P b):st(a),en(b){}
};
int chk_inter(Line p,Line q){
	P&a=p.st,&b=p.en,&c=q.st,&d=q.en;
	int t1 = ccw(a,c,d) , t2 = ccw(b,c,d);
	int t3 = ccw(c,a,b) , t4 = ccw(d,a,b);
	if(t1==0 && t2==0){
		if(b<a) swap(a,b);
		if(d<c) swap(c,d);
		return !(b<c || d<a);
	}
	return t1*t2<=0 && t3*t4<=0;
}
P parrallel_inter(Line p,Line q){
	P&a=p.st,&b=p.en,&c=q.st,&d=q.en;
	if(a<b)
		if(c<d)
			return a<c?c:a;
		else
			return 0.5*(a+c);
	else
		if(d<c)
			return c<a?c:a;
		else
			return 0.5*(a+c);
}
P inter(Line p,Line q){
	P&a=p.st,&b=p.en,&c=q.st,&d=q.en;
	int t1 = ccw(a,c,d) , t2 = ccw(b,c,d);
	if(t1 == 0 && t2 == 0)
		return parrallel_inter(p,q);
	b-=a; d-=c;
	C t = cross(c-a,d) / cross(b,d);
	return a + t*b;
}
struct Event{
	int type,a,b; 
	//type 0 : a to b
	//type 1 : a with b
	//type 2 : a collide with wall
	C t1,t2;
	Event(int x,int y,int z,C d,C e){
		type = x; a = y; b = z;
		t1 = d; t2 = e; 
	}
	bool operator<(Event&tmp){
		return t1<tmp.t1;
	}
};
int main(){
	ios::sync_with_stdio(!cin.tie(0));
	cout<<fixed; cout.precision(2);
	// input
	int n,L; cin>>n>>L;
	vector<Line> v;
	for(int i=0;i<n;i++){
		C a,b,c,d; cin>>a>>b>>c>>d;
		c = a + L*(c-a); d = b + L*(d-b);
		v.push_back(Line(P(a,b),P(c,d)));
	}
	
	// Prepare Events
	vector<Event> T;
	
	// between Snails
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
		Line&a = v[i], &b = v[j];
		if(chk_inter(a,b)){
			P res = inter(a,b);
			C t1 = dist(res-a.st), t2 = dist(res-b.st);
			if(res.X<0 || res.X>L || res.Y<0 || res.Y>L) continue;
			if(same(t1,t2)){
				T.emplace_back(0,i,j,t1,t1);
			}else if(t1>t2){
				T.emplace_back(1,i,j,t1,t2);
			}else{
				T.emplace_back(1,j,i,t2,t1);
			}
		}
	}
	//between Snails and walls
	P LD = P(0,0), LU = P(0,L), RD = P(L,0), RU = P(L,L);
	v.push_back(Line(LD,LU)); v.push_back(Line(LD,RD));
	v.push_back(Line(LU,RU)); v.push_back(Line(RD,RU));
	
	for(int i=0;i<n;i++) for(int j=n;j<n+4;j++){
		Line&a = v[i], &b = v[j];
		if(chk_inter(a,b)){
			P res = inter(a,b);
			C t1 = dist(res - a.st);
			T.emplace_back(2,i,j,t1,t1);
		}
	}
	
	sort(T.begin(),T.end());
	vector<int> chk(n,0);
	vector<C> boom(n,0.0);
	C ans=0.0;
	for(auto&E : T){
		int type=E.type,a=E.a,b=E.b; C t1=E.t1,t2=E.t2;
		if(type==0){
			if(chk[a] && chk[b]) continue;
			if((!chk[a]||boom[a]>=t1) && (!chk[b]||boom[b]>=t1)){
				if(!chk[a]) boom[a] = t1;
				if(!chk[b]) boom[b] = t1;
				chk[a] = 1; chk[b] = 1;
				ans = t1;
			}
		}else if(type==1){
			if(chk[a]) continue;
			if(!chk[b] || boom[b]>=t2){
				chk[a] = 1;
				boom[a] = t1;
				ans = t1;
			}
		}else{
			if(chk[a]) continue;
			chk[a] = 1;
			boom[a] = t1;
			ans = t1;
		}
	}
	cout<<ans;
}

