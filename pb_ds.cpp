#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using ordered_set=tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>;
using ordered_multiset=tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>;

/*
os.find_by_order(integer) => iterator
os.order_of_key(key) => integer

*/
