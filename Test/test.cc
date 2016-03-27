#include "__rb_tree.h"

template <class T>
struct Node : public rb_tree_node_base<T>
{
	typedef Node<T>* ptr;
	Node() {}
	Node()
	int cnt;
};
rb_tree<int> rb;
typedef rb_tree<int>::ptr_node ptr_node;
void dfs(ptr_node root, ptr_node end)
{
	if(root == end)
		return;
	std::cout << root->key << " " << (root->color == true ? "red" : "black") << std::endl;
	dfs(root->lchild, end);
	dfs(root->rchild, end);
}

int main()
{
	for(int i = 0; i < 12; i++)
		rb.rb_insert(i);
	dfs(rb.getRoot(), rb.getNil());
	rb.erase(3);
	std::cout << "~~~~~~~~~" << std::endl;
	dfs(rb.getRoot(), rb.getNil());
	
	return 0;
}
