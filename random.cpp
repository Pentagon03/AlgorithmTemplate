//[l, r]
template<typename T=int> T get_random_int(T l,T r) {
	//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	// return uniform_int_distribution<T>(l,r)(rng);
	static random_device rd;
	return uniform_int_distribution<T>(l,r)(rd);
}
