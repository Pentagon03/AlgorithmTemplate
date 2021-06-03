struct BIT{
    int n; vector<int> t;
    BIT(int _n=0):n(_n),t(_n+1){}
    void upd(int p,int v){
        for(;p<=n;p+=p&-p)
            t[p]+=v;
    }
    int qry(int p){
        int res = 0;
        for(;p>0;p-=p&-p)
            res += t[p];
        return res;
    }
};
