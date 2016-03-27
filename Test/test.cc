#include "__rb_tree.h"

rb_tree<int> rb;
typedef typename rb_tree<int>::ptr_node ptr_node;
void dfs(ptr_node root, ptr_node end) {
	if(root == end)
		return ;
	dfs(root->lchild, end);
	std::cout << root->key << " " << (root->color == true ? "red" : "black") << std::endl;
	std::cout << (root->lchild->parent->key) << " " << (root->rchild->parent->key) << std::endl;
	dfs(root->rchild, end);
}

typedef typename rb_tree<int>::ptr_node ptr_node;
void dfs1(ptr_node root, ptr_node end) {
	if(root == end)
		return ;
	std::cout << root->key << " " << (root->color == true ? "red" : "black") << std::endl;

	dfs1(root->lchild, end);
	dfs1(root->rchild, end);
}

int main()
{
	for(int i = 0; i < 20; i++)
		rb.rb_insert(i);
	rb_tree<int>::iterator it;
	it = rb.begin();
	while(it != rb.end()) {
		std::cout << (it->key) << std::endl;
		++it;
	}

	std::cout << "~~~~~~~~~~~~~~" << std::endl;
	dfs1(rb.getRoot(), rb.getNil());
//	std::cout << rb.getRoot()->lchild->key <<std::endl;
//	std::cout << rb.getRoot()->rchild->key <<std::endl;

	std::cout << "~~~~~~~~~~~~~" << std::endl;
	dfs(rb.getRoot(), rb.getNil());
	return 0;
}
