/*Solution
https://acmicpc.net/problem/16357

일단 좌표압축하고 시작 (시작 좌표와 끝 좌표만 봐도 충분)
차이배열 기법 통해서 각 y축에 몇개의 직사각형이 있는지 기록함

구간을 s,e라 하면 s에 대해 정렬하고 레이지 세그를 하나 관리하는데 
첫번째 직선은 차이배열의 값으로 고르고, 두번째 직선은 일단 레이지에서 현재 직사각형을 제거해준 다음 최댓값을 구해준다. 계속 제거해나가면 된다.
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

// range addition update, range maximum query
struct node{
    int mx, lzadd;
    node(int a=-inf,int b=0):mx(a), lzadd(b){}
    void apply(const node&p, int l, int r){
        // [l, r]
        if(p.lzadd != 0){
            mx += p.lzadd;
            lzadd += p.lzadd;
        }
    }
};

/*
to use multiple segs,
you must get rid of default parameters in the function
and manually use seg.st in parameters
*/
int st;
struct seg{
    vector<node> t;
    // int st;
    seg(int n = (1<<17)){
        st = 1;
        while(st < n) st <<= 1;
        t.resize(st<<1);
    }
    void build(vector<node>&v){
        for(int i=0;i<size(v);i++)
            t[st+i] = v[i];
        for(int i=st-1; i>=1; i--)
            pull(i);
    }
    void push(int i, int l, int r){
        if(i < st){
            int m = (l+r) / 2;
            t[2*i].apply(t[i], l, m);
            t[2*i+1].apply(t[i],m+1,r);
            t[i] = node(t[i].mx, 0);
        }
    }
    void pull(int i){
        t[i].mx = max(t[2*i].mx, t[2*i+1].mx);
    }
    void upd(int x,int y, const node& v, int i=1, int l=0, int r=st-1){
        if(x > r or y < l) return;
        if(x <= l and r <= y){
            t[i].apply(v, l, r);
            return;
        }
        push(i, l, r);
        int m = (l+r)/2;
        upd(x, y, v, 2*i, l, m);
        upd(x, y, v, 2*i+1, m+1, r);
        pull(i);
    }
    int qry(int x,int y, int i=1, int l=0, int r=st-1){
        if(x > r or y < l) return -inf;
        if (x <= l and r <= y) return t[i].mx;
        push(i, l, r);
        int m = (l+r)/2;
        int ans = max(qry(x, y, 2*i, l, m),qry(x, y, 2*i+1, m+1, r));
        return ans;
    }
};

void solve(){
    int n; cin>>n;
    vector<int> coor;
    vector<pii> v;
    for(int i=0;i<n;i++){
        int x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        // y1>y2
        coor.push_back(y2); coor.push_back(y1);
        v.emplace_back(y2, y1);
    }
    sort(all(coor)); coor.erase(unique(all(coor)), end(coor));
    vector<int> C(size(coor) + 2);
    for(auto&[s,e]:v){
        s = lower_bound(all(coor), s) - begin(coor);
        e = lower_bound(all(coor), e) - begin(coor);
        C[s] += 1; C[e+1] -= 1;
    }
    
    seg f(size(coor));
    vector<node> g(size(coor));
    for(int i=0;i<size(coor);i++){
        if(i>0) C[i] += C[i-1];
        g[i] = node(C[i]);
    }
    f.build(g);

    sort(all(v));
    int ans = 0;
    for(int i=0;i<n;i++){
        f.upd(v[i].first, v[i].second, {0, -1});
        if(i+1 == n or v[i+1].first != v[i].first)
            ans = max(ans, C[v[i].first] + f.t[1].mx);
    }
    cout<<ans<<nl;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int tc = 1;
    // cin >> tc;
    for(cur_tc=1;cur_tc<=tc;++cur_tc) solve();
    return 0;
}
