#ifndef __LIST_
#define __LIST_

#include "memory.h"
#include "algorithm.h"

template <class T>
struct __list_node
{
	T data;
	__list_node<T> *last_node, *next_node;
	__list_node() : last_node(NULL), next_node(NULL) {}
	__list_node(const T& val) : data(val), last_node(NULL), next_node(NULL) {}
	__list_node(const T& val, const __list_node<T>*& last_node, 
				const __list_node<T>*& next_node) : data(val), last_node(last_node), next_node(next_node) {}
};

template <class T>
struct __list_iterator
{
	typedef T value_type;
	typedef tinyAr::bidirectional_iterator_tag iterator_category;
	typedef T* pointer;
	typedef __list_iterator<T> self;

	pointer node;
	
	__list_iterator() : node(NULL) {}
	__list_iterator(pointer pt) : node(pt) {}

	T& operator*() const {
		return *node;
	}

	T* operator->() const {
		return node;
	}

	self& operator++() {
		node = node->next_node;
		return *this;
	}
	
	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--() {
		node = node->last_node;
		return *this;
	}

	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}

	bool operator== (__list_iterator<T> it) {
		return it.node == node;
	}

	bool operator!= (__list_iterator<T> it) {
		return it.node != node;
	}
};

template <class T>
class list
{
public:
	typedef __list_node<T> value_type;
	typedef value_type* pointer;
	typedef value_type& reference;
	typedef __list_iterator<__list_node<T> > iterator;
	typedef list<T> self;

	list() : __size(0), finish(new value_type) { 
		finish->next_node = finish.node;
		finish->last_node = finish.node;
	}
	
	list(iterator l, iterator r) : __size(0), finish(new value_type) {
		insert(finish, l, r);
	}
	
	~list() {
		clear();
	}

	iterator push_back(const T& val) {
		return insert(finish, val);
	}
	
	void pop_back() {
		erase(iterator(finish->last_node));
	}
	
	T& front() {
		return begin()->data;
	}

	T& back() {
		return (--end())->data;
	}

	iterator begin() const {
		return finish->next_node;
	}

	iterator end() const {
		return finish;
	}
	
	int size() {
		return __size;
	}
	
	bool empty() {
		return __size == 0;
	}

	iterator insert(iterator pos, const T& val) {
		iterator ret(new value_type(val));
		ret->last_node = pos->last_node;
		ret->next_node = pos.node;
		pos->last_node->next_node = ret.node;
		pos->last_node = ret.node;
		++__size;
		return ret;
	}
	
	int insert(iterator pos, iterator l, iterator r) {
		int ret = 0;
		--r;
		while(r != l) {
			insert(pos, r->data);
			--r;
			++ret;
		}
		insert(pos, r->data);
		return ret + 1;
	}

	iterator erase(iterator pos) {
		iterator tmp(pos->next_node);
		pos->next_node->last_node = pos->last_node;
		pos->last_node->next_node = pos->next_node;
		tinyMemo::destroy(&pos->data);
		alloc.deallocate(pos.node, 1);
		--__size;
		return tmp;
	}
	
	iterator erase(iterator l, iterator r) {
		while(l != r) {
			if(l != finish)
				erase(l++);
			else
				++l;
		}
		return r;
	}
	
	int erase(iterator l, iterator r, const T& val) {
		int ret = 0;
		while(l != r) {
			if(l == finish) { ++l; continue; }

			if(l->data == val) {
				erase(l++);
				++ret;
			}else 
				++l;
		}
		return ret;
	}
	
	int erase(const T& val) {
		return erase(begin(), end(), val);
	}
	
	/*int merge(self& lt) {
		self::iterator back_it = --lt.end();
		self::iterator front_it = ++lt.end();  
		front_it->last = finish->last_node;
		finish->last_node->next_node = front_it.node;
		back_it->next_node = finish.node;
		finish->last_node = back_it.node;
		__size += lt.size();
		lt.clear();
		return __size;
	}*/

	void clear() {
		erase(begin(), end());
	}
	
	template <class compare>
	void sort(iterator l, iterator r, const compare& cmp) {
		iterator ret, limit(l->last_node);
		T t;
		for(; l != r; ++l) {
			t = l->data;
			ret = l, --ret;
			for(; ret != limit; --ret) {
				if(ret->data == t || cmp(ret->data, t)) 
					break;
				else
					ret->next_node->data = ret->data;
			}
			ret->next_node->data = t;
		}
	}
	
	template <class compare>
	void sort(const compare& cmp) {
		sort(finish->next_node, finish, cmp);
	}

	void sort() {
		sort(finish->next_node, finish, tinyAr::less<T>());
	}

	void sort(iterator l, iterator r) {
		sort(l, r, tinyAr::less<T>());
	}
private:
	iterator finish;
	int __size;
	std::allocator<value_type> alloc;
};
#endif
