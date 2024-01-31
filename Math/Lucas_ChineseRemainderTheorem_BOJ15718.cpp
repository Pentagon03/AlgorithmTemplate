/*Solution
https://acmicpc.net/problem/15718

마지막에 죽어야 하기 때문에 m>1인 경우만 고려하자.
m-1개의 날이 모두 1 이상이 되도록 n개를 적당히 분배해야 한다.
x1 + x2 + ... + xm-1 = n - m + 1(xi는 0 이상)

m-1Hn-m+1
= n-1Cn-m+1 = n-1Cm-2

구현 참고: https://anz1217.tistory.com/109
*/

#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define sp ' '
#define dbg(i) cerr<<#i<<sp<<i<<endl
#define all(v) begin(v),end(v)
// #define int long long
using ll = long long;
using pii = pair<int,int>;
int cur_tc;
constexpr int N = 1e5 + 7, inf = (int)1e9 + 7, mod = (int)1e9 + 7;
constexpr ll linf = (ll)4e18 + 7;

ll ext_gcd(ll a, ll b, ll& x, ll& y) {
    assert(a>=0 && b>=0); // it actually works when a<0 or b<0
    ll g = a;
    x = 1; y = 0;
    // note that x and y are swapped
    if(b != 0) g = ext_gcd(b, a%b, y, x), y -= a/b*x; 
    return g;
}
ll inv(ll a, ll m){
    // return x that a * x = 1 mod m
    ll x, y; 
    ll g = ext_gcd(a, m, x, y);
    if(g != 1) return -1;
    return (x%m + m) % m;
}

map<int, vector<ll>> fac;
// constexpr ll linf = (ll)4e18 + 7
ll ncr(ll n, ll r, ll p = linf){
    if(n<r) return 0;
    if(fac.count(p) == 0){
        vector<ll> fact(p, 1);
        for(int i=1;i<p;i++) fact[i] = i * fact[i-1] % p;
        fac[p] = fact;
    }
    auto&fact = fac[p];
    return fact[n] * inv(fact[n-r] * fact[r] % p, p) % p;
    // ll res = 1;
    // for(int i=1;i<=n;i++) res = res * i % p;
    // ll t = 1;
    // for(int i=1;i<=r;i++) t = t * i % p;
    // for(int i=1;i<=n-r;i++) t = t * i % p;
    // res = res * inv(t,p) % p;
}

ll lucas(ll n, ll r, ll p){ 
    // p는 소수
    ll ans = 1;
    while(ans > 0 && (n>0||r>0)){
		ans = ans * ncr(n % p, r % p, p) % p;
        n /= p; r /= p;
	}
    return ans;
}

using pll = pair<ll,ll>;
// (a, m) -> a mod m
ll crt(vector<pll> const& cgv) {
    // assume they are all coprimes each other
    ll M = 1;
    for (auto const& cg : cgv) 
        M *= cg.second;
    ll solution = 0;
    for (auto const& cg: cgv) {
        ll a_i = cg.first;
        ll M_i = M / cg.second;
        ll N_i = inv(M_i, cg.second);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}

void solve(){
    int n, m; cin>>n>>m;
    if(m==1){
        if(n==0) cout<<1<<nl;
        else cout<<0<<nl;
        return;
    }
    if(n < m-1){
        cout<<0<<nl;
        return;
    }
    // 100007 = 97 * 1031
    ll a1 = lucas(n-1, m-2, 97);
    ll a2 = lucas(n-1, m-2, 1031);
    vector<pll> v = {pll(a1,97), pll(a2,1031)};
    cout<<crt(v)<<nl;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int tc = 1;
    cin >> tc;
    for(cur_tc=1;cur_tc<=tc;++cur_tc) solve();
    return 0;
}
