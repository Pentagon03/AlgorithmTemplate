#include <bits/stdc++.h>
 
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
 
typedef long long ll;

unsigned hash_f(unsigned x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}
 
struct chash {
    ll operator()(ll x) const { return hash_f(x); }
};
 
const ll N = 1e18;

gp_hash_table<ll, ll, chash> seg;
 
ll get(ll x) {
    auto res = seg.find(x);
    return (res == seg.end()) ? 0 : res->second;
    // return (seg.find(x) == seg.end()) ? 0 : seg[x];
}
void modify(ll p, ll val) {
    for (seg[p += N] = val; p > 0; p >>= 1) {
        seg[p >> 1] = get(p) + get(p ^ 1);
    }
}
 
ll query(ll l, ll r) {
    ll res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += get(l++);
        if (r & 1)
            res += get(--r);
    }
    return res;
}
 
