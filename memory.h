#ifndef __MEMORY_
#define __MEMORY_

#include <cstdio>
#include <new>
#include <cstdlib>
#include <memory>
#include "algorithm.h"

namespace tinyMemo
{
	template <class it>
	class traits
	{
	public:
		typedef typename it::value_type value_type;
		typedef typename it::iterator_category iterator_category;
	};

	template <class it>
	class traits<it*>
	{
	public:
		typedef it value_type;
		typedef tinyAr::random_access_iterator_tag iterator_category;
	};

	template <class it>
	class traits<const it*>
	{
	public:
		typedef it value_type;
		typedef tinyAr::random_access_iterator_tag iterator_category;
	};

	template <class iterator>
	void destroy(iterator a, iterator b){
		typedef typename traits<iterator>::value_type T;
		while(a != b) {
			a->~T();
			++a;
		}
	}
	
	template <class iterator>
	void destroy(iterator p){
		typedef typename traits<iterator>::value_type T;
		p->~T();
	}
}

#endif
