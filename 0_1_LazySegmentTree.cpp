//https://howtoliveworldnice.tistory.com/612
#pragma GCC optimize("Ofast")
//Always Do Your Best Ku!
#include<bits/stdc++.h>
using namespace std;
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v).size())
#define nl '\n'
#define sp ' '
using ll = long long;
using pii = pair<int,int>;
const int inf = 1e9;
#define dbg(X) cerr<<#X<<'='<<X<<nl
#define GET_TC 0

struct Node{
    int l[2]{},r[2]{};
    bool lz=0;
    Node(){}
    Node(char c){l[1]=r[0]=1;if(c==')')flip();}
    void flip(){swap(l[0],l[1]); swap(r[0],r[1]);}
    void merge(const Node&a,const Node&b){
        for(int i=0;i<2;i++){
            l[i] = a.l[i] + max(0,b.l[i]-a.r[i]);
            r[i] = b.r[i] + max(0,a.r[i]-b.l[i]);
        }
        if(lz) flip();
    }
}; 
struct Seg{
    vector<Node> tree; int b = 1; 
    Seg(int n = 1){
        while(b<n) b<<=1;
        tree.assign(b<<1,Node());
    }
    void init(int p,int s,int e,string&str){
        if(s==e){
            tree[p] = Node(str[s-1]);
            return;
        }
        init(p<<1,s,s+e>>1,str); init(p<<1|1,s+e+2>>1,e,str);
        tree[p].merge(tree[p<<1],tree[p<<1|1]);
    }
    Node query(int p,int s,int e,int l,int r,int mode){
        Node res;
        if(l<=s && e<=r){
            if(mode==1) tree[p].lz ^= 1, tree[p].flip();
            else res = tree[p];
        }else if(!(e<l || r<s)){
            Node L = query(p<<1,s,s+e>>1,l,r,mode);
            Node R = query(p<<1|1,s+e+2>>1,e,l,r,mode);
            if(mode==1) tree[p].merge(tree[p<<1],tree[p<<1|1]);
            else{
                res.merge(L,R);
                if(tree[p].lz) res.flip(); //[s,e]와 연관된 부분만 res에 들어가 있으므로
            }
        }
        return res;
    }
};
void solve(int TC){
    int n,q; string s; cin>>n>>s>>q;
    Node x;
    Seg f(n);
    f.init(1,1,n,s);
    while(q--){
        int t,a,b; cin>>t>>a>>b;
        x = f.query(1,1,n,a,b,t);
        if(t==2) cout<<(b-a+1+x.l[0]+x.r[0])<<nl;
    }
}

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int T = 1; if(GET_TC) cin >> T;
    for(int i=1;i<=T;i++) solve(i);
}
