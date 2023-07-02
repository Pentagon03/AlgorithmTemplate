#include<bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define repr(l,r) for(int i=(l);i<=(r);i++)
#define repd(l,r) for(int i=(r);i>=(l);i--)
void chk_range(int x,int l,int r){
    if(l>r) swap(l,r);
    assert(l<=x && x<=r);
}
//[l, r]
template<typename T=int> T get_random_int(T l,T r) {
	//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	// return uniform_int_distribution<T>(l,r)(rng);
	static random_device rd;
	return uniform_int_distribution<T>(l,r)(rd);
}
constexpr int SZ = 25, N = 5e5, M = 1e6, mod = 1e9+7;

void make_tc(int k){
	string prefix = "data",num=to_string(k),in=".in";
	string I = prefix+num+in;
	freopen(I.c_str(),"w",stdout);
	int n = get_random_int(1,N), m = get_random_int(1,M);
	printf("%d %d\n",n,m);
}

void solve(){
  int n,m; scanf("%d %d",&n,&m);
	assert(1<=n && n<=N && 1<=m && m<=M);
	printf("%d\n",n+m);
}

void solve_tc(int k){
	string C = "data",num=to_string(k),in=".in",out=".out";
	string I = C+num+in , O = C+num+out;
	freopen(I.c_str(),"r",stdin); // 입력 파일 처리
	freopen(O.c_str(),"w",stdout); // 출력 파일 처리
	solve(); 
}

int main(){
	repr(tc,1,10){
		make_tc(tc);
		solve_tc(tc);
	}
}
