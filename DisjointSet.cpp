#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 1e5+10;

int rt[N];
void init(int n){
    for(int i=1;i<=n;i++){
        rt[i] = i;
        //initialize size, vectors or smth
    }
}
int find(int k){
    if(k==rt[k]) return k;
    return rt[k] = find(rt[k]);
}
void merge(int a,int b){
    a = find(a); b = find(b);
    if(a==b) return;
    //random merge
    if(a^b) rt[a] = b;
    else rt[b] = a;
}

int main(){
    ios::sync_with_stdio(!cin.tie(0));
    int n; cin>>n;
    init(n);
    
}
