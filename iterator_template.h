#ifndef __iterator_template_
#define __iterator_template_

#include "algorithm.h"

template <class T>
struct iterator_template
{
	typedef T value_type;
	typedef T* pointer;
	
	pointer node;

	T& operator*() const {
		return *node;
	}

	T* operator->() const {
		return node;
	}
};
#endif
