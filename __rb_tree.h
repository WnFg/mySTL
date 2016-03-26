#ifndef __RB_TREE_
#define __RB_TREE_

#include "algorithm.h"
#include <iostream>

typedef bool rb_tree_color;
const rb_tree_color rb_tree_black = false;
const rb_tree_color rb_tree_red = true;

template <class T>
struct rb_tree_node_base
{
	typedef T key_type;
	typedef rb_tree_node_base<T>* ptr_node;
	
	ptr_node parent, lchild, rchild;
	key_type key;
	rb_tree_color color;	
	
	rb_tree_node_base() {}
	rb_tree_node_base(const T& val, ptr_node nil_node) : key(val), lchild(nil_node),
														 rchild(nil_node) {}
	
	bool operator< (rb_tree_node_base node) {
		return key < node.key;
	}
	
	bool operator== (rb_tree_node_base node) {
		return key == node.key;
	}

	bool operator!= (rb_tree_node_base node) {
		return key != node.key;
	}

	static ptr_node leftmost_node(ptr_node node, ptr_node end) {
		while(node->lchild != end) 
			node = node->lchild;
		return node;
	}

	static ptr_node rightmost_node(ptr_node node, ptr_node end) {
		while(node->rchild != end) 
			node = node->rchild;
		return node;
	}
};

template <class node_type>
class rb_tree_iterator
{
public:
	rb_tree_iterator() : node(NULL) {}
	node_type* node;
};

template <class T, class compare = tinyAr::less<T> >
class rb_tree
{
public:
	typedef rb_tree_node_base<T> node_type;
	typedef node_type* ptr_node;
	typedef rb_tree_iterator<node_type> iterator;
	typedef T value_type;
	

	rb_tree() : nil_node(new node_type), __size(0) {nil_node->color = rb_tree_black;}
	
	int size() {
		return __size; 
	}

protected:
	void left_roate(ptr_node& __root) {
		ptr_node node = __root;
		if(node != root) {
			bool left = isLchild(node);
			if(left)
				node->parent->lchild = node->rchild;
			else
				node->parent->rchild = node->rchild;
		}else {
			root = node->rchild;
		}
		__root = node->rchild;
		node->rchild = __root->lchild;
		__root->parent = node->parent;
		node->parent = __root;
		__root->lchild = node;
	}
	
	void right_roate(ptr_node& __root) {
		ptr_node node = __root;
		if(node != root) {
			bool left = isLchild(node);
			if(left)
				node->parent->lchild = node->lchild;
			else
				node->parent->rchild = node->lchild;
		}else {
			root = node->lchild;
		}
		__root = node->lchild;
		node->lchild = __root->rchild;
		__root->parent = node->parent;
		node->parent = __root;
		__root->rchild = node;
	}
	
	inline bool isLchild(node_type* node) {
		return node == node->parent->lchild;
	}
	
	void insert_case_a(node_type* new_z) {
		new_z->lchild->color = rb_tree_black;
		new_z->rchild->color = rb_tree_black;
		rb_insert_fixup(new_z);
	}
	
	void __insert_case_b_3(node_type* gparent) {
		right_roate(gparent);
		gparent->rchild->color = rb_tree_red;
		gparent->color = rb_tree_black;
	}

	void __insert_case_b_2(node_type* parent) {
		left_roate(parent);
		__insert_case_b_3(parent->parent);
	}
	
	void __insert_case_b_1(node_type* gparent) {
		std::cout << "case_b_1" << std::endl;
		left_roate(gparent);
		gparent->lchild->color = rb_tree_red;
		gparent->color = rb_tree_black;
	}
	
	void __insert_case_b_0(node_type* parent) {
		right_roate(parent);
		__insert_case_b_1(parent->parent);
	}

	void insert_case_b(node_type* gparent, node_type* parent, node_type* z) {
		bool a = isLchild(parent);
		bool b = isLchild(z);
		if(a && b) {
			__insert_case_b_3(gparent);
		} else if(a && !b) {
			__insert_case_b_2(parent);
		} else if(!a && !b) {
			__insert_case_b_1(gparent);
		} else
			__insert_case_b_0(parent);
	}

	void rb_insert_fixup(node_type* z) {
		if(z == root) {
			z->color = rb_tree_black;
			return ;
		}

		if(z->parent == root) 
			return ;

		node_type* parent = z->parent;
		node_type* gparent = parent->parent;
		if(isLchild(parent)) {
			if(gparent->rchild->color == rb_tree_red) 
				insert_case_a(gparent);
			else {
				insert_case_b(gparent, parent, z);		
				return ;
			}
		}else {
			if(gparent->lchild->color == rb_tree_red) {
				insert_case_a(gparent);
				std::cout << "cvdf" << std::endl;
			}
			else {
				std::cout << "fixup" << std::endl;
				insert_case_b(gparent, parent, z);
				return ;
			}
		}
	}


	void roate(node_type* node, bool left) {
		if(left)
			left_roate(node);
		else
			right_roate(node);
	}
	
	inline node_type* getBrother(node_type* node, bool left) {
		return left ? node->parent->rchild : node->parent->lchild;
	}

	inline node_type* getChild(node_type* node, bool left) {
		return left ? node->lchild : node->rchild;
	}

	void __rb_delete_case_4(node_type* parent, node_type* node, bool a) {
		node_type* brother = getBrother(node, a);
		parent->color = rb_tree_black;
		getChild(brother, !a)->color = rb_tree_black;
		tinyAr::swap(parent->color, brother->color);
		roate(parent, a);
	}

	void __rb_delete_case_3(node_type* parent, node_type* node, bool a) {
		node_type* brother = getBrother(node, a);		
		node_type* child = getChild(brother, a);
		tinyAr::swap(brother->color, child->color);
		roate(brother, !a);
		__rb_delete_case_4(parent, node, a);
	}

	void __rb_delete_case_2(node_type* parent, bool a) {
		node_type* child = getChild(parent, !a);
		child->color = rb_tree_red;
		rb_delete_fixup(parent);		
	}
	
	void __rb_delete_case_1(node_type* parent, node_type* node, bool a) {
		node_type* brother = getBrother(node, a);
		tinyAr::swap(brother->color, parent->color);
		roate(parent, a);
		rb_delete_fixup(node);
	}

	void rb_delete_fixup(node_type* x) {
		if(x == root)
			return;
		if(x->color == rb_tree_red) {
			x->color = rb_tree_black;
			return;
		}
		node_type* parent = x->parent;
		bool left = isLchild(x);
		node_type* brother = getChild(parent, !left);
		if(brother->color == rb_tree_black) {
			if(getChild(brother, !left)->color == rb_tree_red)
				__rb_delete_case_4(parent, x, left);
			else if(getChild(brother, left)->color == rb_tree_red)
				__rb_delete_case_3(parent, x, left);
			else 
				__rb_delete_case_2(parent, left);	
		}else 
			__rb_delete_case_1(parent, x, left);
	}

public:
	ptr_node getRoot() {
		return root;
	}
	
	ptr_node getNil() {
		return nil_node;
	}

	void rb_delete(node_type* node) {
		--__size;
		node_type* x;
		if(node->lchild == nil_node || node->rchild == nil_node)
			x = node;
		else{
			x = node_type::leftmost_node(node->rchild, nil_node); 
			tinyAr::swap(node->key, x->key);
		}

		node_type* child = x->lchild != nil_node ? x->lchild : x->rchild;

		if(isLchild(x)) {
			x->parent->lchild = child;
			child->parent = x->parent;
		}else {
			x->parent->rchild = child;
			child->parent = x->parent;
		}
		if(x->color == rb_tree_black)
			rb_delete_fixup(child);
		delete x;
	}

	bool rb_insert(const value_type& val) {
		if(__size == 0) {
			root = new node_type(val, nil_node);
			root->color = rb_tree_black;
			__size = 1;
			return true;
		}

		node_type* node = new node_type(val, nil_node);
		node->color = rb_tree_red;

		node_type* parent;
		node_type** ptr_ptr_node = &root;
		while(*ptr_ptr_node != nil_node) {
			if(**ptr_ptr_node == *node) 
				return false;
			
			parent = *ptr_ptr_node;
			if(*node < **ptr_ptr_node) {
				ptr_ptr_node = &(*ptr_ptr_node)->lchild;
			}else {
				ptr_ptr_node = &(*ptr_ptr_node)->rchild;
			}
		}
	//	std::cout << parent->key << std::endl;
		*ptr_ptr_node = node;
		node->parent = parent;
		if(parent->color == rb_tree_red) {
			rb_insert_fixup(node);
		}
		__size++;
		return true;
	}
	
protected:
	int __size;
	node_type* root;
	node_type* nil_node;

};

#endif
