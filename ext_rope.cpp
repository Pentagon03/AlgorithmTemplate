#include<ext/rope>
using namespace __gnu_cxx;
void solve(){
	rope<char> r;
	string s; cin>>s;
	r.append(s.c_str()); // string to rope
	/*
	vector functions like push_back(), size(), empty() can be used
	crope == rope<char> , can put normal char* string
	insert(int x, crope r1): Inserts the contents of r1 before the xth element. Time Complexity: For Best Case: O(log N) and For Worst Case: O(N).
	erase(int x, int l): Erases l elements, starting with the xth element. Time Complexity: O(log N).
	substr(int x, int l): Returns a new rope whose elements are the l characters starting at the position x. Time Complexity: O(log N).
	replace(int x, int l, crope r1): Replaces the l elements beginning with the xth element with the elements in r1. Time Complexity: O(log N).
	concatenate(+): concatenate two ropes using the ‘+’ symbol. Time Complexity: O(1).
	r[id] == r.at(id)
	*/
}
