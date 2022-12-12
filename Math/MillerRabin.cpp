using ull = unsigned long long;
constexpr int SZ = 100000; 
bitset<SZ> isp; vector<int> prlist;
void Sieve(){
    isp.set(); isp[0]=isp[1]=false;
    for(int i=2;i<SZ;i++){
        if(isp[i]){
            prlist.push_back(i);
            if(1LL*i*i>=SZ) continue;
            for(int j=i*i;j<SZ;j+=i) isp[j] = false;
        }
    }
}
ull MulMod(ull a,ull b,ull c){return (__uint128_t)a*b%c;}
ull PowMod(ull a,ull b,ull c){
    ull ans = 1;
    while(b>0){
        if(b&1) ans = MulMod(ans,a,c);
        a = MulMod(a,a,c);
        b >>= 1;
    }
    return ans;
}
const int p32[]={2, 7, 61}, p64[]={2, 325, 9375, 28178, 450775, 9780504, 1795265022};
bool MillerRabin(ull n, ull a){ // is n prime based on a
    if(a % n == 0) return true; // can't check
    int cnt = __builtin_ctzll(n-1);
    ull p = PowMod(a, n-1>>cnt, n);
    if(p==1 || p==n-1) return true;
    while(cnt--) if((p=MulMod(p,p,n))==n-1) return true;
    return false;
}
bool IsPrime(ull n){
    if(n<SZ) return isp[n];
    // check some base primes
    for(int i=0;i<5;i++) if(n%prlist[i]==0) return false;
    for(int p:p64) if(!MillerRabin(n,p)) return false;
    return true;
}
