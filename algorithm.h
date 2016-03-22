#ifndef __ALGORITHM_
#define __ALGORITHM_

#include "memory.h"

namespace tinyAr
{
	struct input_iterator_tag {};  // 只读迭代器，支持++
	struct output_iterator_tag {};	// 只写迭代器, 支持++
	struct forward_iterator_tag : public input_iterator_tag {}; // 允许读写，支持++
	struct bidirectional_iterator_tag : public forward_iterator_tag {}; // 可双向移动，支持++，--
	struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // 可随机访问
	
	template <class T>
	class less
	{
	public:
		bool operator() (const T& a, const T& b) const {
			return a < b;
		}
	};

	template <class T>
	class greater
	{
	public:
		bool operator() (const T& a, const T& b) const {
			return a > b;
		}
	};
	
	template <class iterator>
	typename iterator::iterator_category  // 获取迭代器类型
	getIteratorType(iterator) {
		return typename iterator::iterator_category();
	}

	template <class iterator>
	random_access_iterator_tag		// 指针型迭代器
	getIteratorType(iterator*) {
		return random_access_iterator_tag(); 
	}

	template <class iterator, class T>
	iterator find(iterator l, iterator r, const T& value) {
		while(l != r) {
			if(*l == value)
				return l;
			++l;
		}
		return r;
	}

	template <class iterator>
	iterator getPreIterator(iterator it, bidirectional_iterator_tag) {
		return --it;
	}

	template <class iterator>
	iterator getPreIterator(iterator it) {
		return getPreIterator(it, getIteratorType(it));
	}
}

#endif
