#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9+7;
int startup=1,fac[1000001]={1};
inline int FastPow(int x,int n=mod-2){
    int ans = 1;
    while(n>0){
        if(n&1)
            ans = 1LL*ans*x%mod;
        x=1LL*x*x%mod;
        n>>=1;
    }
    return ans;
}
inline int nCr(int n,int r){
    if(startup){
        for(int i=1;i<=n;i++)
            fac[i] = 1LL*fac[i-1]*i%mod;
        startup = 0;
    }
    return 1LL*fac[n]*FastPow(1LL*fac[r]*fac[r]%mod)%mod;
}
int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n,r; cin>>n>>r;
    cout<<nCr(n,r);
}
