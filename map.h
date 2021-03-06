#ifndef __MAP_
#define __MAP_

#include "__rb_tree.h"

template <class T1, class T2>
struct element_type
{
	element_type() {}
	element_type(const T1& a, const T2& b) : first(a), second(b) {}

	inline bool operator< (const element_type<T1, T2>& x) const {
		return first < x.first;
	}
	
	inline bool operator<= (const element_type<T1, T2>& x) const {
		return first <= x.first;
	}

	inline bool operator> (const element_type<T1, T2>& x) const {
		return first > x.first;
	}

	inline bool operator>= (const element_type<T1, T2>& x) const {
		return first >= x.first;
	}

	inline bool operator== (const element_type<T1, T2>& x) const {
		return first == x.first;
	}

	inline bool operator!= (const element_type<T1, T2>& x) const {
		return first != x.first;
	}

	T1 first;
	T2 second;
};

template <class T1, class T2, class BaseNode_type = rb_tree_node_base<element_type<T1, T2> > >
class map
{
public:
	typedef element_type<T1, T2> key_value_type;
	typedef key_value_type* pointer;
	typedef key_value_type& reference;
	typedef const key_value_type* const_pointer;
	typedef const key_value_type& const_reference;
	typedef T1 key_type;
	typedef T2 value_type;

	typedef typename rb_tree<key_value_type>::iterator iterator;
	typedef BaseNode_type node_type;
	typedef node_type* ptr_node;
	
	map() : rb(new rb_tree<key_value_type>) {}
	~map() { delete rb;}

	iterator find(const key_type& val) {
		return rb->find(key_value_type(val, T2()));
	}
	
	iterator lower_bound(const key_type& key) {
		return rb->lower_bound(key_value_type(key, value_type()));
	}
	
	iterator upper_bound(const key_type& key) {
		return rb->upper_bound(key_value_type(key, value_type()));
	}

	iterator insert(const key_type& v1, const value_type& v2) {
		return rb->rb_insert(key_value_type(v1, v2));
	}
	
	int size() {
		return rb->size();
	}
	
	bool empty() {
		return rb->size() == 0;
	}
	
	bool erase(const key_type& val) {
		return rb->erase(key_value_type(val, T2()));
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
	
	value_type& operator[] (const key_type& key) {
		iterator it(find(key));
		if(it == rb->end())
			it = rb->rb_insert(key_value_type(key, value_type()));
		return it->second;
	}
	
protected:
	rb_tree<key_value_type>* rb;
};

#endif
