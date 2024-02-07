/*Solution
https://acmicpc.net/problem/3295

고를 수 있는 간선의 최댓값.

그 후로 모르겠어서 답지 봄.
링 혹은 선형 배열이라는 뜻은
한 정점에 대하여 최대 1번 들어가거나, 나갈 수 있다는 뜻과 같음.
그래. 이분매칭이다.

bipartite matching도 struct화 시킴.
쾨닉의 정리 적용하여 min vertex cover도 구할 수 있음.
https://m.blog.naver.com/kks227/220967185015
https://m.blog.naver.com/kks227/220960915791
참고
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


struct BipartiteMatching{
    vector<int> vis, A, B;
    vector<vector<int>> g;
    int pv;
    BipartiteMatching(int n,int m):g(n),A(n,-1), vis(m,0), B(m,-1){};
    void add_edge(int a,int b){
        g[a].push_back(b);
    }
    bool dfs(int x){
        for(int nx:g[x]){
            if(vis[nx]!=pv && B[nx]==-1){
                vis[nx] = pv;
                A[x] = nx;
                B[nx] = x;
                return true;
            }
        }
        for(int nx:g[x]){
            if(vis[nx]!=pv){
                vis[nx] = pv;
                if(dfs(B[nx])){
                    A[x] = nx;
                    B[nx] = x;
                    return true;
                }
            }
        }
        return false;
    }
    int max_matching(){
        pv = 0;
        int ans = 0;
        for(int i=0;i<size(g);i++){
            ++pv;
            if(dfs(i)) ++ans;
        }
        return ans;
    }
    vector<pii> get_max_matching(){
        if(pv == 0) max_matching();
        vector<pii> ans;
        for(int i=0;i<size(A);i++){
            if(A[i]!=-1){
                ans.emplace_back(i, A[i]);
            }
        }
        return ans;
    }
    //증명: https://m.blog.naver.com/kks227/220967185015
    vector<pii> get_min_vertex_cover(){
        if(pv == 0) max_matching();
        vector<vector<int>> g2(size(B));
        for(int i=0;i<size(A);i++){
            for(int x:g[i]){
                g2[x].push_back(i);
            }
        }
        vector<bool> chkA(size(A)), chkB(size(B));
        function<void(int,int)> dfs2 = [&](int x,int team){
            auto&chk = team?chkB:chkA;
            if(chk[x]) return;
            chk[x] = true;
            auto&rg = team?g2:g;
            for(int nx: rg[x])
                if((team == 0 && A[x] != nx) || (team == 1 && B[x] == nx))
                    dfs2(nx, !team);
        };
        for(int i=0;i<size(A);i++)
            if(A[i] == -1)
                dfs2(i, 0);
        vector<pii> ans;
        for(int i=0;i<size(A);i++)
            if(!chkA[i])
                ans.emplace_back(0, i);
        for(int i=0;i<size(B);i++)
            if(chkB[i])
                ans.emplace_back(1, i);
        return ans;
    }
    vector<pii> get_max_independent_set(){
        auto mvc = get_min_vertex_cover();
        vector<bool> chkA(size(A)), chkB(size(B));
        for(auto[c,x]: mvc)
            (c?chkB:chkA)[x] = true;
        vector<pii> ans;
        for(int i=0;i<size(A);i++)
            if(!chkA[i])
                ans.emplace_back(0, i);
        for(int i=0;i<size(B);i++)
            if(!chkB[i])
                ans.emplace_back(1, i);
        return ans;
    }
};
void solve(){
    int n,m; cin>>n>>m;
    BipartiteMatching bm(n,n);
    while(m--){
        int a, b; cin>>a>>b;
        bm.add_edge(a,b);
    }
    cout<<bm.max_matching()<<nl;
}

signed main(){
    cin.tie(0)->sync_with_stdio(0);
    // cout<<fixed<<setprecision(15);
    int tc = 1;
    cin >> tc;
    for(cur_tc=1;cur_tc<=tc;++cur_tc) solve();
    return 0;
}
