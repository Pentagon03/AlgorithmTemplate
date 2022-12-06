string A,B;
const int MX = 5e4 + 10;
const int ALP = 26;
using ull = unsigned long long;
ull dt[(MX>>6)+1],S[ALP][(MX>>6)+1];

#include<immintrin.h>
void solve(){
    cin>>A>>B;
	int n=A.length(),m=B.length(),ans=0;
	for(int i=0;i<m;i++) S[B[i]-'A'][i>>6]|=1ULL<<(i&63);
	int t = (m>>6)+1;
	for(int i=0;i<n;i++){
		for(int j=0, c=1, mc=0; j<t;j++){
			ull x = dt[j] | S[A[i]-'A'][j], y;
			mc = _subborrow_u64(mc, x, (dt[j]<<1)|c, &y);
            c = dt[j] >> 63;
			dt[j] = x & (x^y);
		}
	}
	for(int i=0;i<t;i++) ans += __builtin_popcountll(dt[i]);
	// for(int i=0;i<m;i++) ans += !!(dt[i>>6] & (1ULL<<(i&63)));
	cout<<ans<<nl;
}
