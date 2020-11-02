//https://www.acmicpc.net/problem/2150

#include<bits/stdc++.h>
#define nl '\n'
#define sp ' '
using namespace std;
#define all(v) (v).begin(),(v).end()
const int N = 1e4 + 5;

int n,m,vis[N],pv;
vector<int> v[N],rev[N],f;
vector<vector<int>> scc;

void dfs(int k){
    vis[k]=1;
    for(int x:v[k])
        if(!vis[x])
            dfs(x);
    f.push_back(k);
}
void Adfs(int k,vector<int>&v){
    vis[k]=1; v.push_back(k);
    for(int t:rev[k])
        if(!vis[t])
            Adfs(t,v);
}
bool cmp(vector<int> a,vector<int> b){
    return a.front()<b.front();
}
int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    cin>>n>>m;
    while(m--){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        rev[b].push_back(a);
    }
    for(int i=1;i<=n;i++)
        if(!vis[i])
            dfs(i);
    fill(vis,vis+n+1,0);
    reverse(all(f));

    int cnt=0;
    for(int k : f){
        if(vis[k]) continue;
        vector<int> t;
        Adfs(k,t); scc.push_back(t); ++cnt;
    }

    for(vector<int>&t:scc) sort(all(t));
    sort(all(scc),cmp);

    cout<<cnt<<'\n';
    for(vector<int>&t:scc){
        for(int i:t)
            cout<<i<<sp;
        cout<<-1<<nl;
    }
}
