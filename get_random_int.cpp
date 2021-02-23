template<typename T=int> T get_random_int(T l,T r) {
	static random_device rd;
	return uniform_int_distribution<T>(l,r)(rd);
}
