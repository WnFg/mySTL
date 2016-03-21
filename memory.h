#ifndef __MEMORY_
#define __MEMORY_

#include <cstdio>
#include <new>
#include <cstdlib>

namespace tinyMemo
{
	template <class it>
	class traits
	{
	public:
		typedef typename it::value_type value_type;
	};

	template <class it>
	class traits<it*>
	{
	public:
		typedef it value_type;
	};

	template <class it>
	class traits<const it*>
	{
	public:
		typedef it value_type;
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
