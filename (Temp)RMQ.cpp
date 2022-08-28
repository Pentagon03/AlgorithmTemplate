void solve(){
    //전처리
    const int MAXN = 25; 

    //로그 배열 만들기
    int Log[MAXN+1];
    Log[1] = 0;
    for (int i = 2; i <= MAXN; i++)
        Log[i] = Log[i/2] + 1;
    int N; cin>>N;
    const int K = Log[N];
    // N+1의 크기를 가진 arr 배열 선언
    int arr[N+1] , spt[N+1][ K + 1 + 1];
    // N * (log(N)+1)
    for(int i=1;i<=N;i++) cin>>arr[i];
    //전처리
    for (int i = 1; i <= N; ++i)
        spt[i][1] = arr[i];

    for (int j = 2; j <= K+1; ++j) {
        for (int i = 1; i + (1 << j-1) <= N+1; ++i) {
            spt[i][j] = max(spt[i][j-1], spt[i + (1 << (j - 2))][j - 1]);
        }
    }

    //쿼리
    int m; cin>>m;
    while(m--){
        int a,b; cin>>a>>b;
        int j = Log[b-a+1];
        int ans = max(spt[a][j+1], spt[b-(1<<j)+1][j+1]);
        cout<<ans<<nl;
    }
}
