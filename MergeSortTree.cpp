const int MXN = 1<<20;
struct Seg{
    int st;
    vector<vector<int>> tree;
    Seg(int k=MXN){
        st = 1<<int(ceil(log2(k)));
        tree.resize(st<<1);
    }
    void build(){
        for(int i=st-1;i>0;i--){
            merge(all(tree[i<<1]),all(tree[i<<1|1]),back_inserter(tree[i]));
        }
    }
    vector<int>& elem(int k){
        return tree[st+k];
    }
    int cnt(int nd,int k){
        return tree[nd].size()-(upper_bound(all(tree[nd]),k)-tree[nd].begin());
    }
    ll query(int l,int r,int k){
        ll ans = 0;
        l+=st; r+=st;
        while(l<=r){
            if(l&1) ans += cnt(l++,k);
            if(!(r&1)) ans += cnt(r--,k);
            l>>=1; r>>=1;
        }
        return ans;
    }
};
