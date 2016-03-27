#ifndef __iterator_template_
#define __iterator_template_

#include "algorithm.h"
#include <iostream>

template <class Category, class T, class Distance = int,
		  class Pointer = T*, class Reference = T&>
struct iterator_template
{
	typedef T value_type;
	typedef Pointer pointer;
	typedef Category iterator_category;
	typedef Reference reference;
	typedef Distance difference_type;

	pointer node;
	
	iterator_template() : node(NULL) {}
	iterator_template(const pointer& p) : node(p) {}

	T& operator*() const {
		return *node;
	}

	T* operator->() const {
		return node;
	}
};
#endif
