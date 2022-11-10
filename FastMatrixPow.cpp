#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using matrix = vector<vector<int>>;
matrix fail = {{-1}};
const int MOD = 1000;
template<typename T>
void init(T&A,int r,int c){
	A.resize(r);
	for(int i=0;i<r;i++) A[i].resize(c);
}
template<typename T>
T operator*(T A,T B){
	int r1=A.size(),c1=A[0].size(),r2=B.size(),c2=B[0].size();
	if(c1!=r2) return fail;
	T C; init(C,r1,c2);
	for(int i=0;i<r1;i++) C[i].resize(c2);
	for(int i=0;i<r1;i++)
		for(int k=0;k<c1;k++){
			const int tmp = A[i][k];
			for(int j=0;j<c2;j++){
				C[i][j] += tmp*B[k][j];
				C[i][j] %= MOD;
			}
		}
	return C;
}

template<typename T1,typename T2>
T1 operator^(T1 A,T2 x){
	if(x==0) return fail;
	T1 ans = A; --x;
	while(x>0){
		if(x&1)
			ans = ans * A;
		x>>=1;
		A = A*A;
	}
	return ans;
}

int main(){
	ios::sync_with_stdio(!cin.tie(0));
	int n; ll B;
	cin>>n>>B;
	matrix A; init(A,n,n);
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)
		cin>>A[i][j];
	matrix&& ans = A^B;
	for(int i=0;i<n;i++) {
		for(int j=0;j<n;j++)
			cout<<ans[i][j]%MOD<<' ';
		cout<<'\n';
	}
	return 0;
}
