#include<bits/stdc++.h>
#define all(v) v.begin(),v.end()
using namespace std;
const int N = 3e5;
using ll = long long;

struct BIT{
    int n;
    vector<int> t;
    void init(int k){
        t.clear();
        n=k; t.resize(n+1);
    }
    void update(int p,int v){
        for(;p<=n;p+=p&-p)
            t[p]+=v;
    }
    int query(int p){
        int res = 0;
        for(;p>0;p-=p&-p)
            res += t[p];
        return res;
    }
};

void solve(){
    int n; cin>>n;
    vector<int> v(n),tmp;
    for(int i=0;i<n;i++)
        cin>>v[i];
    tmp = v;
    sort(all(tmp)); tmp.erase(unique(all(tmp)),tmp.end());
    int m = tmp.size(); ll s = 0;
    for(int i=0;i<n;i++)
        v[i] = lower_bound(all(tmp),v[i])-tmp.begin();

    BIT f;
    f.init(m);
    vector<int> C(m);
    for(int i=0;i<n;i++){
        int val = m - v[i] + 1;
        s += f.query(val-1);
        f.update(val,1);
    }
    cout<<s;
}

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    solve();
    return 0;
}

