#ifndef __iterator_template_
#define __iterator_template_

#include "algorithm.h"

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

	T& operator*() const {
		return *node;
	}

	T* operator->() const {
		return node;
	}
};
#endif
