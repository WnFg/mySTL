#include "__rb_tree.h"

rb_tree<int> rb;
int main()
{
	rb.rb_insert(1);
	rb.rb_insert(3);
	rb.rb_insert(5);
	std::cout << (rb.lower_bound(2)->key) << std::endl;
	std::cout << (rb.upper_bound(2)->key) << std::endl;
	return 0;
}
