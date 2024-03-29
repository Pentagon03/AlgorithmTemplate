//http://boj.kr/cc4de6e6b13f4a9590c1a8a4a2fac275
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define sp ' '
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define all(v) v.begin(),v.end()
#define sz(v) ((int)(v).size())
// #define GET(n) int n; cin>>n
#ifndef ONLINE_JUDGE
#define dbg(x) cerr<<#x<<": "<<x<<nl;
#else
#define dbg(x) NULL;
#endif 
// #define IV(v,n) vector<int> v(n); for(auto&k:v) cin>>k
using ll = long long;
using pii = pair<int,int>;

// #include <unistd.h>
// namespace io {
// 	const signed IS=1<<22, OS=1<<20;
// 	char I[IS+1],*J=I,O[OS],*K=O;

// 	inline void daer(){if(J>=I+IS-64){char*p=I;do*p++=*J++;while(J!=I+IS);p[read(0,p,I+IS-p)]=0;J=I;}}
// 	template<int N=10,typename T=int>inline T getu(){daer();T x=0;int k=0;while(*J<=32)++J;do x=x*10+*J-'0';while(*++J>='0'&&++k<N);return x;}
// 	struct f{f(){I[read(0,I,IS)]=0;}}flu;
// };
// using namespace io;

string A, B;
const int MX = 5e4 + 10;
const int ALP = 26;
using ull = unsigned long long;
ull dt[(MX>>6)+1], S[ALP][(MX>>6)+1];
inline bool _test(ull arr[],int x){
	return (bool)(arr[x>>6] & (1ULL << (x&63)));
}
inline void _set(ull arr[],int x){
	arr[x>>6] |= 1ULL << (x&63);
}

#include<immintrin.h>
vector<int> getLCSdp(string&A,string&B){
	int n=A.length(),m=B.length(),ans=0;
	int siz = (m>>6)+1;

	// Init
	for(int i=0;i<siz;i++) dt[i] = 0;
	for(int i=0;i<ALP;i++) for(int j=0;j<siz;j++) S[i][j] = 0;
	
	for(int i=0;i<m;i++) S[B[i]-'A'][i>>6]|=1ULL<<(i&63);
	for(int i=0;i<n;i++){
		for(int j=0, c=1, mc=0; j<siz;j++){
			ull x = dt[j] | S[A[i]-'A'][j], y;
			mc = _subborrow_u64(mc, x, (dt[j]<<1)|c, &y);
            c = dt[j] >> 63;
			dt[j] = x & (x^y);
		}
	}
    vector<int> v(m+1);
	rep(i,m) v[i+1] = v[i] + !!(dt[i>>6] & (1ULL<<(i&63)));
	return v;
}
std::string getLCS(string A,string B){
    //LCS of A and B
    int n = A.length(), m = B.length();
    string ans = "";
    if(!m) return ans;
    if(n==1){
        for(int i=0;i<m;i++)
            if(B[i]==A[0]){
                ans = string(1,A[0]);
                break;
            }
    }else if(m==1){
        for(int i=0;i<n;i++)
            if(A[i]==B[0]){
                ans = string(1,B[0]);
                break;
            }
    }else{ //n>1 && m>1
        int mid = n/2;
        string A1 = A.substr(0,mid);
        string A2 = A.substr(mid,n-mid);
        reverse(all(A2));
        string B1, B2 = B;
        reverse(all(B2));
        vector<int>&&dp1 = getLCSdp(A1,B);
        vector<int>&&dp2 = getLCSdp(A2,B2);
        int best = 0;
        for(int i=0;i<=m;i++)
            if(dp1[i]+dp2[m-i] > dp1[best]+dp2[m-best])
                best = i;
        B1 = B.substr(0,best);
        B2 = B.substr(best,m-best);
        reverse(all(A2));
        ans = getLCS(A1,B1) + getLCS(A2,B2);
    }
    // dbg(A); dbg(B); dbg(ans);
    return ans;
}

void solve(){
    string A,B;
    cin>>A>>B;
    string ans = getLCS(A,B);
    cout<<ans.length()<<nl<<ans<<nl;
}
    

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int T = 1;
    // cin >> T;
    for(int i=1; i<=T; i++){
        // cout<<"Case "<<i<<": ";
        solve();
    }
}
