#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
const int N = 1e5 + 5, INF = 1e9;

#define fi first
#define se second
vector<pii> g[N];
int dis[N];
void Dijkstra(int s = 1)
{
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    fill(dis, dis + N, INF);
    dis[s] = 0;
    pq.push(pii(0, s)); //Warning : weight first, node second
    while (!pq.empty()) {
        auto t = pq.top(); pq.pop();
        int x = t.fi, w = t.se;
        if (w > dis[x]) continue;
        for (auto nt : g[x]) {
            int nx = nt.fi, nw = nt.se; //Warning : node first,weight second
            if (w + nw < dis[nx]) {
                dis[nx] = w + nw;
                pq.push(pii(dis[nx], nx));
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(!cin.tie(0));
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
