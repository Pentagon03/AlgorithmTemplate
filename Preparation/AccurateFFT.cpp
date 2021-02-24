typedef long double RN;
typedef complex<RN> base;
const RN PI = acos(RN(-1));
void fft(vector <base> &a, bool invert)
{
    int n = sz(a);
    for (int i=1,j=0;i<n;i++){
        int bit = n >> 1;
        for (;j>=bit;bit>>=1) j -= bit;
        j += bit;
        if (i < j) swap(a[i],a[j]);
    }
    for (int len=2;len<=n;len<<=1){
		vector<base> w(len/2);
		for(int i=0;i<len/2;i++){
			RN ang = 2*PI*i/len*(invert?-1:1);
			w[i] = base(cos(ang),sin(ang));
		}
        for (int i=0;i<n;i+=len){
            for (int j=0;j<len/2;j++){
                base u = a[i+j], v = a[i+j+len/2]*w[j];
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
            }
        }
    }
    if (invert){
        for (int i=0;i<n;i++) a[i] /= n;
    }
}
template<typename T=ll>
void multiply(const vector<T> &a,const vector<T> &b,vector<T> &res)
{
    vector <base> fa(all(a)), fb(all(b));
    int n = 1;
	//다항식을 제곱하는 경우 2*n까지 계수가 가능하다
	while(n<sz(a)+sz(b)-1) n<<=1;
    fa.resize(n); fb.resize(n);
    fft(fa,false); fft(fb,false);
    for (int i=0;i<n;i++) fa[i] *= fb[i];
    fft(fa,true);
    res.resize(n);
	int SZ=0;
    for (int i=0;i<n;i++) {
		res[i] = T(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
		if(res[i]>0) SZ=i+1;
	}
	// res.resize(SZ); //for size OPT
}
//출처: https://blog.myungwoo.kr/54 [PS 이야기]
