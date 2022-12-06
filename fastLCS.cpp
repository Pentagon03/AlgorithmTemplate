const int MX = 1e4 + 10;
const int ALP = 26;
using ull = unsigned long long;
ull dt[(MX>>6)+1], S[ALP][(MX>>6)+1];
#include<immintrin.h>
int getLCSdp(string&A,string&B){
	int n=A.length(),m=B.length(),ans=0;
	int siz = (m>>6)+1;

	// Init
	for(int i=0;i<siz;i++) dt[i] = 0;
	for(int i=0;i<ALP;i++) for(int j=0;j<siz;j++) S[i][j] = 0;
	
	for(int i=0;i<m;i++) S[B[i]-'a'][i>>6]|=1ULL<<(i&63);
	for(int i=0;i<n;i++){
		for(int j=0, c=1, mc=0; j<siz;j++){
			ull x = dt[j] | S[A[i]-'a'][j], y;
			mc = _subborrow_u64(mc, x, (dt[j]<<1)|c, &y);
            c = dt[j] >> 63;
			dt[j] = x & (x^y);
		}
	}
	for(int i=0;i<siz;i++) ans += __builtin_popcountll(dt[i]);
	return ans;
}
