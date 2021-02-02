#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define task "pieaters"
#define pll pair<ll, ll>
#define pii pair<ll, pll>
#define fi first
#define se second
const ll mod = 1e9 + 7;
const ll N = 3e5+5;
 
using ull = unsigned long long;
using namespace std;
ll n, m, t, k, T, ans, a[N], b[N], tong, d[N], u, v;
vector<ll> kq, res;
struct dang
{
    ll x, y, w;
}e[N];
bool cmp(const dang&u, const dang&v)
{
    return u.w < v.w;
}
void sol()
{
    cin >> n;
    tong = 0;
    ans = 0;
    for(int i = 1;i <= n; i ++)
    {
        cin >> a[i];
    }
    sort(a+1, a+1+n);
    for(int i = 3; i <= n; i ++)
    {
        ll lf = 1, rt = i-1, mid;
        while(lf <= rt)
        {
            mid = (lf + rt) / 2;
            if(a[mid] < a[i] - 2)lf = mid + 1;
            else rt = mid - 1;
        }
        bool ok = true;
        if(a[lf] + 2 >=  a[i] && lf < i-1)
        {
            ok = true;
            k = lf;
        k = i-1-k;
        if(ok)ans += k * (k + 1) / 2;
        }
 
    }
    cout << ans << '\n';
}
 
int main()
{
    if(fopen(task".in", "r")){
       freopen(task".in", "r", stdin);
       freopen(task".out", "w", stdout);
    }
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int ntest;
    ntest = 1;
    cin >> ntest;
    while(ntest -- > 0)
    sol();
 
}