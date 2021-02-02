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
using pll = pair<ll,ll>;
#define fi first
#define se second

// using C = double;
// using P = pair<C,C>;
// const double eps = 1e-9;
// #define X first
// #define Y second

#define V(X) vector<X>
#define pb push_back
#define eb emplace_back
#define ep emplace
#define all(v) (v).begin(),(v).end() 
#define compress(v) sort(all(v)),v.erase(unique(all(v)),v.end())

#define rep(i,n) for(int i=0;i<(n);i++)
#define rep1(i,n) for(int i=1;i<=(n);i++)
#define repr(i,a,b) for(int i=(a);i<=(b);i++)
#define repd(i,b,a) for(int i=(b);i>=(a);i--)

#define nl '\n'
#define sp ' '
#define yes(T) cout<<(T?"YES\n":"NO\n")
#define prt(x) cerr<<#x<<": "<<x<<nl
#define pprt(x) cout<<(x)
#define left(i) ((i)<<1)
#define right(i) ((i)<<1|1)
void dbg(string s = "STILL WORKING"){puts(s.c_str());}

int TC = 1;
bool getTC = 0, printTC = 0, useDouble = 0;
const bool startup = [](){
	// #define ONLINE_JUDGE
	#ifdef ONLINE_JUDGE
	ios::sync_with_stdio(false); cin.tie(0); 
	#endif
	if(getTC) cin>>TC;
	if(useDouble) cout<<fixed<<setprecision(12);
	return true;
}();

// int n;
// vector<int> v(3);
// void input(){
// 	cin>>n; v.assign(n,0);
// 	rep(i,n) cin>>v[i];
// }

const int N = 1e5+5, inf = 1e9, mod = 1e9+7;

void solve(){

}

int main(){
	rep1(tc,TC){
		if(printTC) cout<<"Case #"<<tc<<": ";
		solve();
	}
	return 0;
}


// Solution
/*



*/

