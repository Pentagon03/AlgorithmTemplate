const unsigned p_base = 257, p_mod = 1e9+7;
string s;
unsigned hashstr(const string& s,int n){
	ll res=0;
	for(int i=0;i<n;i++){
		res = res*p_base + s[i];
		res %= p_mod;
	}
	return res;
}
void solve(){
  int n,m; cin>>n>>m;
	cin>>s;
	vector<int> Hash(n-m+1);
	ll res=0,power=1;
	rep(i,m) power=power*p_base%p_mod;
	for(int i=0;i<n-m+1;i++){
		if(i==0){
			Hash[i] = hashstr(s,m);
		}else{
			Hash[i]=((ll)Hash[i-1]*p_base+s[i+m-1])%p_mod;
			Hash[i] = (Hash[i] - power*s[i-1]%p_mod)%p_mod;
			if(Hash[i]<0) Hash[i] += p_mod;
		}
		//prt(i); prt(Hash[i]); 
	}
}
