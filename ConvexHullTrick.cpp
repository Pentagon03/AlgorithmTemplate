const int N = 2e5+5, inf = 1e9, mod = 1e9+7;
struct Line{
    int a; ll b;
    Line(int x=0,ll y=0):a(x),b(y){}
    double f(double x){return a*x+b;}
};
inline double inter(Line&f,Line&g){
    return (double)(g.b-f.b)/(f.a-g.a);
}
//CHT는 항상 항상 항상 오버플로우 가능성을 명심해야 한다. 
Line st[N];
struct CHT{
	int n=0, p=0; //n은 현재 직선의 개수, p는 마지막으로 살펴본 직선의 위치
    CHT(){n=p=0;}
	void insert(Line t){
		while(n>1 && inter(st[n-2],t) > inter(st[n-1],t))
            --n;
        st[n++] = t;
	}
	//좌표가 증가하는 순서 
    double query(double x){
        if(n==0) return 0;
		p=min(n-1,p);
		while(p+1<n && inter(st[p],st[p+1]) < x) p++;
		return st[p].f(x);
	}
	//좌표의 순서를 모름 -> 이분탐색 
	double query_bs(double x){
        if(n==0) return 0;
		int s=0,e=n-1;
		while(s<e){
			int m = s+e>>1;
			if(inter(st[m],st[m+1]) < x) s=m+1;
			else e=m;
		}
		return st[e].f(x);
	}
};
