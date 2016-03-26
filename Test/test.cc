#include "__rb_tree.h"
#include <iostream>

rb_tree<int> rb;
typedef typename rb_tree<int>::node_type* ptr_node;
void dfs(ptr_node root, ptr_node end){
	if(root == end) {
		return ;
	}
	dfs(root->lchild, end);
	std::cout << root->key << std::endl;
	dfs(root->rchild, end);
}
int main()
{
	for(int i = 0; i < 20; i++) {
		rb.rb_insert(i);
	}
/*	std::cout << rb.size() << std::endl;
	std::cout << rb.root->key << std::endl;
	std::cout << rb.root->lchild->key << std::endl;
	std::cout << rb.root->rchild->key << std::endl;
*/
dfs(rb.root, rb.nil_node);
	return 0;
}

