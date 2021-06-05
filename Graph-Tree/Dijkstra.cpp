#include <bits/stdc++.h>
using namespace std;
using ll = long long;

using pii = pair<int, int>;
const int N = 1e5 + 5;

vector<pii> g[N];
int dis[N];
void Dijkstra(int s = 1)
{
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    const int INF = 1e9;
    fill(dis, dis + N, INF);
    pq.push(pii(dis[s] = 0, s)); //Warning : weight first, node second
    while (!pq.empty()) {
        auto t = pq.top(); pq.pop();
        int w,x; tie(w,x) = t;
        if (w > dis[x]) continue;
        for (auto nt : g[x]) {
            int nx,nw; tie(nx,nw) = nt; //Warning : node first, weight second
            if (w + nw < dis[nx]) {
                dis[nx] = w + nw;
                pq.push(pii(dis[nx], nx));
            }
        }
    }
}

void solve(int TC = -1){
     int n, m;
    cin >> n >> m;
    while (m--) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back(pii(b, w));
        g[b].push_back(pii(a, w));
    }
    Dijkstra();
}
int main()
{
    ios::sync_with_stdio(!cin.tie(0));
    solve();
}
