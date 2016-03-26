#include "__rb_tree.h"

rb_tree<int> rb;
typedef typename rb_tree<int>::ptr_node ptr_node;
void dfs(ptr_node root, ptr_node end) {
	if(root == end)
		return ;
	dfs(root->lchild, end);
	std::cout << root->key << std::endl;
	dfs(root->rchild, end);
}
int main()
{
	for(int i = 0; i < 20; i++)
		rb.rb_insert(i);
	dfs(rb.getRoot(), rb.getNil());
	rb.rb_delete(rb.getRoot());
	dfs(rb.getRoot(), rb.getNil());
	std::cout << rb.getRoot()->key << std::endl;
	return 0;
}
