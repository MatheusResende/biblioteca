#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<
	int,
	null_type,
	less<int>,
	rb_tree_tag,
	tree_order_statistics_node_update>
ordered_set;


ordered_set os;
os.insert(int x);//inserts x
os.size();//size
os.order_of_key(int key);//index that contains key
*s.find_by_order(k);// find element with given order