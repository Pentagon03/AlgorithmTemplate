const unsigned p_cnt = 2, p_base = 26, p_mod[p_cnt] = {(int)1e9+7,(int)1e9+9};
vector<ll> Hash,power;
string s;
void solve(){
	int n,k; cin>>n>>k;
	vector<int> s(n);
	rep(i,n) cin>>s[i];
	int l = 0, r = n;
	while(l+1<r){
		int m = l + r >> 1;
		int flg=0;
		unordered_map<ll,int> chk;
		power.assign(p_cnt,1); Hash.assign(p_cnt,0);
		for(int i=0;i<n;i++){ 
			for(int j=0;j<p_cnt;j++){
				Hash[j]=(Hash[j]*p_base+s[i])%p_mod[j];
				if(i<m) power[j]=power[j]*p_base%p_mod[j];
				else Hash[j] = (Hash[j] - power[j]*s[i-m])%p_mod[j];
				if(Hash[j]<0) Hash[j] += p_mod[j];
			}
			ll hval = Hash[0]<<32 | Hash[1];
			if(++chk[hval]>=k){
				l = m;
				flg = 1;
				break;
			}
		}
		if(!flg)
			r = m;
	}
	cout<<l;
}
