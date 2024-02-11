/*Solution
https://acmicpc.net/problem/17399

a,b,c의 외심을 찾는 문제.
외심은 두 조건을 만족한다.
1. 동일성 -> dist(a,b) = dist(b,c) = dist(c,a)
2. 최소성

a와 b의 가장 가까운 중점을 M이라 해보자.
M에서 a와 b쪽이 아닌 다른 방향 (부모 혹은 자식)으로 간 것들도
모두 a와 b의 중점이 될 것이다. 거리를 d라 하자.
dist(M,c) = d라면 정답은 그대로 M이된다. (다른 방향으로 옮기면 d가 증가한다.)
dist(M,c) != d라면 M을 적당히 옮겨서 c와의 거리를 맞춰야 한다.
적당히 옮겨서 외심 M이 존재한다고 가정하자. 놀랍게도 이때의 M은 (a와 c의 중점) 혹은 (b와 c의 중점) 중 하나다.

만약 M이 (a,b) 의 중점도 아니고 (b,c)의 중점도 아니고, (c,a)의 중점도 아닌 경우가 있다고 가정하자.
이때 어떤 방향으로 한칸 움직이든 M과 a,b,c와의 거리는 모두 같다. (모두 각 쌍의 중점에서 시작하는 가지 위에 있기 때문).
따라서 (b,c)의 중점 쪽으로 한칸 이동한 M'을 생각하자.
(1)M과 (b,c)와의 거리는 1 감소한다.
(2) M과 (a,b), (a,c)와의 거리는 1 증가하거나 감소한다.
(3) (2)에서, (1)에 의해 항상 1 감소해야 한다. 

따라서 M'과 (a,b,c)와의 거리는 모두 1 감소하였다. 

즉, M은 외심의 최소성에 모순이다.
결론적으로 외심은 최소 세 개의 중점 중 하나다.

여기서 더 확장하여 n개의 중점은 nC2개의 중점 쌍 중 하나임을 보일 수 있다.
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

const int MXH = 18;
int par[MXH][N], dep[N];
vector<int> g[N];
void dfs(int x,int p,int d){
    dep[x] = d;
    par[0][x] = p;
    for(int i=1;par[i-1][x];i++)
        par[i][x] = par[i-1][par[i-1][x]];
    for(int nxt: g[x])
        if(nxt != p)
            dfs(nxt, x, d+1);
}
int up(int x,int d){
    for(int i=MXH-1;i>=0;i--)
        if((d>>i) & 1)
            x = par[i][x];
    return x;
}
int lca(int x,int y){
    if(dep[x]<dep[y]) swap(x,y);
    x = up(x, dep[x]-dep[y]);
    if(x==y) return x;
    for(int i=MXH-1;i>=0;i--){
        if(par[i][x] != par[i][y]){
            x = par[i][x];
            y = par[i][y];
        }
    }
    return par[0][x];
}
int tree_dist(int x,int y){
    int l = lca(x, y);
    return dep[x] + dep[y] - 2 * dep[l]; 
}
int tree_mid(int x, int y){
    int d = tree_dist(x, y);
    if(d & 1) return -1;
    if(dep[x]<dep[y]) swap(x,y);
    return up(x, d/2);
}
int qry(vector<int> nodes){
    int n = size(nodes);
    if(n == 0) return -1;
    if(n == 1) return nodes[0];
    if(n == 2) return tree_mid(nodes[0], nodes[1]);
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++){
            int mid = tree_mid(nodes[i], nodes[j]);
            if(mid == -1) continue;
            int d = tree_dist(nodes[i],nodes[j]) / 2;
            bool flag = true;
            for(int k=0;k<n;k++){
                if(d != tree_dist(nodes[k], mid)){
                    flag = false;
                    break;
                }
            }
            if(flag) return mid;
        }
    return -1;
}
void solve(){
    int n; cin>>n;
    for(int i=0;i<n-1;i++){
        int x, y; cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    dfs(1,0,0);
    int q; cin>>q;
    while(q--){
        int a,b,c; cin>>a>>b>>c;
        cout<<qry({a,b,c})<<nl;
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
