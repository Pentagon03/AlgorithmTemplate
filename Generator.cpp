#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (n); i++)
#define repr(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
const int SZ = 25;

const int N = 1e6, M = 1e6;

mt19937 mt(time(NULL));
uniform_int_distribution<int> A(0, N), B(0, M); // 숫자 범위

void make_tc(int k)
{
	string pre = "data", num = to_string(k), in = ".in";
	string I = pre + num + in;
	freopen(I.c_str(), "w", stdout);
	//변경 1번
	int n = A(mt), m = A(mt);
	printf("%d %d\n", n, m);
}

//변경 2번
void solve()
{
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%d\n", n + m);
}

void solve_tc(int k)
{
	string C = "data", num = to_string(k), in = ".in", out = ".out";
	string I = C + num + in, O = C + num + out;
	freopen(I.c_str(), "r", stdin);	 // 입력 파일 처리
	freopen(O.c_str(), "w", stdout); // 출력 파일 처리
	solve();
}

int main()
{
	repr(tc, 1, 10)
	{
		//make_tc(tc);
		solve_tc(tc);
	}
}
