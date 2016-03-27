#ifndef __SET_
#define __SET_

#include "__rb_tree.h"

template <class T, class BaseNode_type = rb_tree_node_base<T> >
class set
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	
	typedef typename rb_tree<T>::iterator iterator;
	typedef BaseNode_type node_type;
	typedef node_type* ptr_node;
	
	set() : rb(new rb_tree<T>) {}
	~set() { delete rb;}

	iterator find(const T& val) {
		return rb->find(val);
	}
	
	int count(const T& val) {
		return rb->find(val) != rb->end();
	}
	
	bool insert(const T& val) {
		return rb->rb_insert(val);
	}
	
	int size() {
		return rb->size();
	}
	
	bool empty() {
		return rb->size() == 0;
	}
	
	bool erase(const T& val) {
		return rb->erase(val);
	}

	void erase(iterator it) {
		rb->erase(it);
	}

	void clear() {
		rb->clear();
	}

	iterator begin() {
		return rb->begin();
	}

	iterator end() {
		return rb->end();
	}
protected:
	rb_tree<T>* rb;
};

#endif
