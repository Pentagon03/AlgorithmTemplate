
// ██████╗░███████╗███╗░░██╗████████╗░█████╗░░██████╗░░█████╗░███╗░░██╗
// ██╔══██╗██╔════╝████╗░██║╚══██╔══╝██╔══██╗██╔════╝░██╔══██╗████╗░██║
// ██████╔╝█████╗░░██╔██╗██║░░░██║░░░███████║██║░░██╗░██║░░██║██╔██╗██║
// ██╔═══╝░██╔══╝░░██║╚████║░░░██║░░░██╔══██║██║░░╚██╗██║░░██║██║╚████║
// ██║░░░░░███████╗██║░╚███║░░░██║░░░██║░░██║╚██████╔╝╚█████╔╝██║░╚███║
// ╚═╝░░░░░╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝░╚═════╝░░╚════╝░╚═╝░░╚══╝

// Problem : 
// bit.ly/pentagon03 
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;
#define all(v) (v).begin(),(v).end() 
#define compress(v) sort(all(v)),v.erase(unique(all(v)),v.end())
#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define repr(i,a,b) for(int i=(a);i<=(b);i++)
#define pb push_back
#define eb emplace_back
#define ep emplace
#define nl '\n'
#define sp ' '
// using C = double;
// using P = pair<C,C>;
#define prt(T) cout<<(T?"YES\n":"NO\n"); return;
void dbg(string s = "STILL WORKING"){puts(s.c_str());}
int TC = 1;
bool getTC = 0, printTC = 0, useDouble = 1;
const bool startup = [](){
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(0); 
	#endif
	if(getTC) cin>>TC;
	if(useDouble) cout<<fixed<<setprecision(12);
	return true;
}();
inline ll mul(int a,int b){return 1LL*a*b;}


const int N = 1010, inf = 1e9, mod = 1e9+7;
int n,m;
vector<int> adj[N];
int vc,vis[N],team[N];
bool dfs(int k){
    for(int nxt:adj[k]){
        if(vis[nxt] != vc){
            vis[nxt] = vc;
            if(!team[nxt] || dfs(team[nxt])){
                team[nxt] = k;
                return true;
            }
        }
    }
    return false;
}
void solve(){
    cin>>n>>m;
    rep1(i,n){
        int k; cin>>k;
        rep(j,k){
            int t; cin>>t;
            adj[i].pb(t);
        }
    }
    int ans=0,chk=0;
    for(int i=1;i<=n;i++){
        ++vc;
        if(dfs(i)) ++ans;
    }
    cout<<ans;
}

int main(){
	rep1(tc,TC){
		if(printTC) cout<<"Case #"<<tc<<": ";
		solve();
	}
	return 0;
}
