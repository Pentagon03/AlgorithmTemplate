const int RANGE = 1e7; 
int pn, spf[RANGE], pr[RANGE]; 
void eulerSieve() { 
    for(int x=2;x<RANGE;x++) { 
        if(!spf[x]) spf[x] = pr[pn++] = x; 
           for(int j = 0; x*pr[j] < RANGE; ++j) { 
            spf[x*pr[j]] = pr[j]; // 수 * spf들에 대해 spf[x*spf] = spf로 칠해준다. 
            if(x % pr[j] == 0) break; // spf[x] == pr[j]이면 그만 둔다. (이 이상 pr이 늘어나면 x * pr에 대해 더 이상 spf가 pr이 아닌 x의 spf) 
            } 
        } 
    }
}
void fac(int x) {
  while(x!=1){
      //do something with spf[x];
      x/=spf[x];
  }
}
