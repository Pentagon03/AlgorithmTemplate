/*Solution
https://acmicpc.net/problem/10067
dp[i][j]: 1~i번 수열을 j번 나눌 때 얻을 수 있는 점수의 최댓값
i1, i2, i3, ... ik
위치 에서 수열을 나눌 때, 순서대로 나누는게 최적임을 증명하자

i1, i2부터 비교해보자.

S는 누적합이다.
i1부터 나눌 때: (S[i1]-S[0]) * (S[n]-S[i1]) + (S[i2]-S[i1])*(S[n]-S[i2])
i2부터 나눌 때: (S[i2]-S[0]) * (S[n]-S[i2]) + (S[i1]-S[0]) * (S[i2]-S[i1])
i1부터 나눌 때에서 빼면 (S[i1]-S[0])(S[n]-S[i2]) - (S[n]-S[i2]) * (S[i1]-S[0]) = 0
따라서 첫 2개에 대해서는 순서를 바꿔도 그 값이 똑같다.

귀납적으로 (i2, i3), ... (ik-1,ik)를 바꿔도 똑같으므로 
어떤 순서로 수열을 나눠도, 그 값은 같다.

따라서 증가하는 i1, i2, ... ik를 적절히 잘 고르면 된다.
i1, i2, i3, ... ,ik 순서대로 수열을 나눈다 하여도 문제가 없다.

dp[i][k]: ai에서 k번째로 나눌 때(i>=k), 가중치의 최댓값
dp[i][k] = max_j(dp[j][k-1] + (S[i]-S[j]) * (S[n]-S[i])) 
= S[i] * (S[n] - S[i]) + max(dp[j][k-1] - S[j] * (S[n]-S[i]))
= S[i] * (S[n] - S[i]) + max(S[j]*S[i] + dp[j][k-1] - S[j]*S[n])
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

struct Rational{
    ll a,b;
    bool operator<(Rational r){
        return a*r.b < b*r.a;
    }
};
struct Line{
    ll a,b; int id;
    ll f(ll x){return a*x+b;}
    friend double inter(const Line&f,const Line&g){
        return (double)(g.b-f.b)/(f.a-g.a);
    }
    friend Rational inter_rat(Line f,Line g){
        if(f.a < g.a) swap(f,g);
        return {g.b-f.b, f.a-g.a};
    }
};
// a가 같을 경우, 직선 삽입 순서에 유의할 것
// upper hull 이면 (a,b)가 작은 순서
// lower hull 이면 (a,b)가 큰 순서
Line st[N];
struct CHT{
    int n=0, p=0; //n은 현재 직선의 개수, p는 마지막으로 살펴본 직선의 위치
    void insert(const Line& t){
        if(n>=1 && st[n-1].a == t.a){
            // upper hull: <= 
            // lower hull: >=
            if(st[n-1].b <= t.b) --n;
            else return; //t doesnt get inserted
        }
        while(n>=2 && !(inter_rat(st[n-2],t) < inter_rat(st[n-1],t)))
            --n;
        st[n++] = t;
    }
    //좌표가 증가하는 순서 
    Line query(ll x){
        if(n==0) return (Line){0,0,-1};
        p=min(n-1,p);
        while(p+1<n && inter_rat(st[p],st[p+1]) < (Rational){x,1}) p++;
        return st[p];
    }
    //좌표의 순서를 모름 -> 이분탐색 
    Line query_bs(double x){
        if(n==0) return (Line){0,0,-1};
        int s=0,e=n-1;
        while(s<e){
            int m = s+e>>1;
            if(inter(st[m],st[m+1]) < x) s=m+1;
            else e=m;
        }
        return st[e];
    }
};

ll S[N];
int pre[N][200+7];
void solve(){
    int n, K; cin>>n>>K;
    for(int i=1;i<=n;i++){
        int x; cin>>x;
        S[i] = S[i-1] + x;
    }
    int last = K;
    vector<ll> pdp(n+1), dp(n+1);
    for(int k=1;k<=K;k++){
        CHT cht; 
        for(int i=k;i<=n-1;i++){
            if(k>1) cht.insert({S[i-1],pdp[i-1] - S[i-1]*S[n], i-1});
            auto t = cht.query(S[i]);
            pre[i][k] = t.id;
            dp[i] = S[i] * (S[n]-S[i]) + t.f(S[i]);
            if(k == K && dp[i] > dp[last])
                last = i;
        }
        pdp = dp;
    }
    ll ans = dp[last];
    vector<int> ansv;
    int id = K;
    while(last > 0){
        ansv.push_back(last);
        last = pre[last][id--];
    }
    // assert(id == 0);
    reverse(all(ansv));

    cout<<ans<<nl;
    for(int x: ansv) cout<<x<<sp;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int tc = 1;
    // cin >> tc;
    for(cur_tc=1;cur_tc<=tc;++cur_tc) solve();
    return 0;
}
