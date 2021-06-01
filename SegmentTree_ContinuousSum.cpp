//Be aware that this tree is full binary tree
template<typename T = ll,const T inf = T(1e18)>
struct SegCon{
    struct Node{
        T mx, rmx, lmx, sum;
        Node(){mx = rmx = lmx = -inf; sum = 0;}
        Node(T v){mx = rmx = lmx = sum = v;}
    }base;
    vector<Node> tree; int b=1;
    SegCon(int n=1){
        while(b<n) b <<= 1;
        tree.resize(b<<1);
    }
    void reset(){tree.assign(b<<1,Node());}
    Node f(const Node&a,const Node&b){
        Node res;
        res.sum = a.sum + b.sum;
        res.lmx = max(a.lmx,a.sum+b.lmx);
        res.rmx = max(b.rmx,b.sum+a.rmx);
        res.mx = max({a.mx,b.mx,a.rmx+b.lmx});
        return res;
    }
    void init(vector<T>&v){
        *this = SegCon(v.size()); 
        for(int i=0;i<v.size();i++) tree[b+i] = Node(v[i]);
        for(int i=b-1;i>=1;i--) tree[i] = f(tree[i<<1],tree[i<<1|1]);
    }
    void upd(int p,T plus){
        if(!plus) return;
        T v = tree[p+=b].sum;  v += plus;
        for(tree[p]=Node(v);p>>=1;) tree[p] = f(tree[p<<1],tree[p<<1|1]);
    } 
    Node qry(int nd,int s,int e,int l,int r){
        if(e<l || r<s) return base;
        if(l<=s && e<=r) return tree[nd];
        return f(qry(nd<<1,s,s+e>>1,l,r),qry(nd<<1|1,s+e+2>>1,e,l,r));
    } T qry(int l,int r){return qry(1,0,b-1,l,r).mx;}
};
