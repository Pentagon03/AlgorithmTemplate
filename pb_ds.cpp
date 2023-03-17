#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using ordered_set=tree<int, null_type, less<int>, rb_tree_tag,tree_order_statistics_node_update>;
using ordered_multiset=tree<int, null_type, less_equal<int>, rb_tree_tag,tree_order_statistics_node_update>;
// for multiset, functions of lower_bound and upper_bound swap.
// lower_bound: first elem that "a[i]<val" is false;
// upper_bound: first elem that "val<a[i]" is true
bool myerase(ordered_multiset&os,int val){
  auto it = os.upper_bound(val); // which is lower_bound
  if(it!=os.end() && *it==val){
    os.erase(it);
    return true;
  }
  return false;
}

/*
os.find_by_order(integer) => iterator
os.order_of_key(key) => integer
*/
