#ifndef __RB_TREE_
#define __RB_TREE_

#include "algorithm.h"
#include <iostream>
#include "iterator_template.h"

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
class rb_tree_iterator : public iterator_template<tinyAr::bidirectional_iterator_tag, node_type>
{
public:
	typedef iterator_template<tinyAr::bidirectional_iterator_tag, node_type> base;

	using typename base::pointer;
	using typename base::value_type;
	using typename base::reference;
	using typename base::iterator_category;
	using typename base::difference_type;
	using base::node;
	
	pointer nil_node;

	typedef rb_tree_iterator<value_type> self;
	
	rb_tree_iterator() : base(NULL), nil_node(NULL) {}
	rb_tree_iterator(pointer p, pointer end) : base(p), nil_node(end)
	{}
	
	self& operator++ () {
		if(node->rchild != nil_node) {
			node = node_type::leftmost_node(node->rchild, nil_node);
		}else {
			while(node->parent != NULL && !isLchild()) {
				node = node->parent;
			}
			if(node->parent != NULL) 
				node = node->parent;
			else
				node = nil_node;
		}
		return *this;
	}

	self operator++ (int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator-- () {
		if(node->lchild != nil_node) {
			node = node_type::rightmost_node(node->lchild, nil_node);
		}else {
			while(node->parent != NULL && isLchild()) {
				node = node->parent;
			}
			if(node->parent != NULL) 
				node = node->parent;
			else
				node = nil_node;
		}
		return *this;
	}

	self operator-- (int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	bool operator== (const self& a) const {
		return node == a.node;
	}

	bool operator!= (const self& a) const {
		return node != a.node;
	}
protected:
	inline bool isLchild() {
		return node->parent->lchild == node;
	}
};

template <class T, class node_type = rb_tree_node_base<T> >
class rb_tree
{
public:
	typedef node_type* ptr_node;
	typedef rb_tree_iterator<node_type> iterator;
	typedef T value_type;
	typedef tinyAr::pair<ptr_node, bool> pair_type;

	rb_tree() : nil_node(new node_type), __size(0) {
		nil_node->color = rb_tree_black;
		iterator_nil.nil_node = iterator_nil.node = nil_node;
	}
	
	~rb_tree() { clear();}

	void clear() {
		__clear(root);
		root = NULL;
		__size = 0;
	}

	int size() {
		return __size; 
	}

protected:
	void __clear(ptr_node node) {
		if(node == NULL || node == nil_node)
			return ;
		__clear(node->lchild);
		__clear(node->rchild);
		delete node;
	}

	void left_roate(ptr_node& __root) {
		ptr_node node = __root;
		__root = __root->rchild;
		if(node == root) {
			root = __root;
			__root->parent = NULL;
		}else {
			bool left = isLchild(node);
			__root->parent = node->parent;
			if(left)
				node->parent->lchild = __root;
			else
				node->parent->rchild = __root;
		}
		node->rchild = __root->lchild;
		__root->lchild->parent = node;
		__root->lchild = node;
		node->parent = __root;
	}
	
	void right_roate(ptr_node& __root) {
		ptr_node node = __root;
		__root = __root->lchild;
		if(node == root) {
			root = __root;
			__root->parent = NULL;
		}else {
			bool left = isLchild(node);
			__root->parent = node->parent;
			if(left)
				node->parent->lchild = __root;
			else
				node->parent->rchild = __root;
		}
		node->lchild = __root->rchild;
		__root->rchild->parent = node;
		__root->rchild = node;
		node->parent = __root;
	}
	
	inline bool isLchild(node_type* node) {
		return node == node->parent->lchild;
	}
	
	void insert_case_a(node_type* new_z) {
		new_z->lchild->color = rb_tree_black;
		new_z->rchild->color = rb_tree_black;
		new_z->color = rb_tree_red;
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
			}
			else {
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
	
	pair_type __find(const value_type& val) const {
		pair_type tmp(NULL, false);  
		ptr_node node = root;
		while(node != nil_node && val != node->key) {
			if(val < node->key) {
				tmp.first = node;
				tmp.second = true;
				node = node->lchild;
			}
			else {
				tmp.first = node;
				tmp.second = false;
				node = node->rchild;
			}
		}
		return tmp;
	}

	iterator __bound(const value_type& val, bool mark) {
		pair_type tmp = __find(val);
		if(tmp.first == NULL)
			return iterator(root, nil_node);
		if(tmp.second) {
			if(tmp.first->lchild->key == val) {
				return iterator(tmp.first->lchild, nil_node);
			}else {
				if(mark)
					return iterator(tmp.first, nil_node);
				else
					return --iterator(tmp.first, nil_node);
			}
		}else {
			if(tmp.first->rchild->key == val) {
				return iterator(tmp.first->rchild, nil_node);
			}else {
				if(mark)
					return ++iterator(tmp.first, nil_node);
				else
					return iterator(tmp.first, nil_node);
			}
		}
	}
	
public:
	inline ptr_node getRoot() {
		return root;
	}
	
	inline ptr_node getNil() {
		return nil_node;
	}
	
	inline iterator begin() {
		return iterator(root, nil_node);
	}
	
	inline iterator end() {
		return iterator_nil;
	}

	void rb_delete(node_type* node) {
		--__size;
		if(__size == 0) {
			delete root;
			root = NULL;
			return ;
		}
		node_type* x;
		if(node->lchild == nil_node || node->rchild == nil_node)
			x = node;
		else{
			x = node_type::leftmost_node(node->rchild, nil_node); 
			tinyAr::swap(node->key, x->key);
		}

		node_type* child = x->lchild != nil_node ? x->lchild : x->rchild;
		nil_node->parent = x;
		
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
		*ptr_ptr_node = node;
		node->parent = parent;
		if(parent->color == rb_tree_red) {
			rb_insert_fixup(node);
		}
		__size++;
		return true;
	}
	
	iterator find(const value_type& val) {
		ptr_node node = root;
		while(node != nil_node && val != node->key) {
			if(val < node->key) 
				node = node->lchild;
			else
				node = node->rchild;
		}
		return iterator(node, nil_node);
	}
	
	inline iterator lower_bound(const value_type& val) {
		return __bound(val, false);
	}

	inline iterator upper_bound(const value_type& val) {
		return __bound(val, true);
	}

	inline void erase(iterator it) {
		rb_delete(&(*it));
	}

	bool erase(const value_type& val) {
		iterator it = find(val);
		if(it == iterator_nil)
			return false;
		erase(it);
		return true;
	}
protected:
	int __size;
	ptr_node root;
	ptr_node nil_node;
	iterator iterator_nil;
};

#endif
