#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+10, lN = 16; // lN = floor(log2(N-1)) + 1

int par[lN+1][N],dep[N];
vector<int> g[N];

void dfs(int k,int p=0){
    int t=1,pp=p;   
    dep[k] = dep[p] + 1;
    par[0][k] = p;
    while(par[t-1][pp]){
        pp = par[t][k] = par[t-1][pp];
        ++t;
    }
    for(int nxt:g[k]) if(nxt!=p)
        dfs(nxt,k);
}

int LCA(int a,int b,int&dis){
    if(dep[a]<dep[b]) swap(a,b);
    int dif = dep[a] - dep[b];
    dis = dif;
    for(int i=0;dif;dif>>=1,i++)
        if(dif&1)
            a = par[i][a];
    if(a==b) return a;
    for(int i=lN;i>=0;i--)
        if(par[i][a] != par[i][b]){
            a=par[i][a]; b=par[i][b];
            dis += 1<<i+1;
        }
    dis += 2;
    return par[0][a];
}

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n; cin>>n;
    for(int i=1;i<n;i++){
        int a,b; cin>>a>>b;
        g[a].push_back(b); g[b].push_back(a);
    }
    dfs(1);
    int a,b,p,d; cin>>a>>b;
    p = LCA(a,b,d);
}
