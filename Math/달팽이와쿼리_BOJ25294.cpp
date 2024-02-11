/*Solution
https://acmicpc.net/problem/25294
달팽이와 쿼리.
아래 함수 참고 
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


/*
find_val(n, x, y)
길이 n(홀수)의 정사각 배열에서
중앙에서 시작한다.
값 1로 시작할 때 중앙 바로 왼쪽부터 (1,0), (0,1), (-1,0), (0,-1) 방향으로 반복해서 달팽이 배열을 만들어나갈 때
9 8 7
2 1 6
3 4 5
(x,y)에 있는 값을 O(1)에 구한다.
*/
int find_val(int n, int x, int y){
    assert(n%2==1 && 1<=x && x<=n && 1<=y && y<=n);
    int base = (n+1)/2;
    x -= base; y -= base;
    int t = max(abs(x), abs(y));
    if(t==0) return 1;
    int start = (2*t - 1) * (2*t - 1);
    int len = (2*t + 1) * (2*t + 1) - start;
    int baselen = len / 4;
    int cur = start;

    // change this for variants
    int sx = -t, sy = -t;
    int dx[] = {1,0,-1,0}, dy[] = {0,1,0,-1};

    for(int i=0;i<4;i++){
        int ex = sx + dx[i]*baselen, ey = sy + dy[i]*baselen;
        auto in_range = [](int v, int x, int y){return min(x,y)<=v && v<=max(x,y);};
        if(in_range(x, sx+dx[i], ex) && in_range(y, sy+dy[i], ey)){
            cur += abs(x - sx) + abs(y - sy);
            break;
        }else{
            sx = ex; sy = ey;
            cur += baselen;
        }
    }
    return cur;
}

/*
find_loc(n, x)
길이 n(홀수)의 정사각 배열에서
중앙에서 시작한다.
값 1로 시작할 때 중앙 바로 왼쪽부터 (1,0), (0,1), (-1,0), (0,-1) 방향으로 반복해서 달팽이 배열을 만들어나갈 때
9 8 7
2 1 6
3 4 5
x 값을 가지는 (i,j) pair을 O(1)에 구한다.
*/
pii find_loc(int n, int x){
    assert(n%2==1 && 1<=x && x<=n*n);
    int base = (n+1)/2;
    int t = sqrt(x)-1;
    while(t*t < x) ++t;
    if(t%2==0) ++t;
    t/=2;
    if(t==0) return pii(base, base);
    int start = (2*t-1)*(2*t-1);
    int len = (2*t+1)*(2*t+1) - start;
    int baselen = len/4;
    int cur = x - start;

    // change this for variants
    int sx = -t, sy = -t;
    int dx[] = {1,0,-1,0}, dy[] = {0,1,0,-1};

    for(int i=0;i<4;i++){
        if(cur<=baselen){
            sx += dx[i]*cur;
            sy += dy[i]*cur;
            break;
        }else{
            sx += dx[i]*baselen;
            sy += dy[i]*baselen;
            cur -= baselen;
        }
    }
    sx += base; sy += base;
    return pii(sx, sy);
}
void solve(){
    int q; cin>>q;
    while(q--){
        int c, n, x, y; cin>>c>>n>>x;
        if(c==1){
            cin>>y;
            int ans = find_val(n,x,y);
            ans = n * n + 1 - ans;
            cout<<ans<<nl;
        }else{
            x = n * n + 1 - x;
            auto[sx, sy] = find_loc(n, x);
            cout<<sx<<sp<<sy<<nl;   
        }
    }
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int tc = 1;
    // cin >> tc;
    for(cur_tc=1;cur_tc<=tc;++cur_tc) solve();
    return 0;
}
