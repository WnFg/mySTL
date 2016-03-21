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
class __list_iterator
{
public:
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

	self operator--() {
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
	typedef T value_type;
};
#endif
