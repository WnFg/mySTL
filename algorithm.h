#ifndef __ALGORITHM_
#define __ALGORITHM_

#include <iostream>
using namespace std;

namespace tinyAr
{
	struct input_iterator_tag {};  // 只读迭代器，支持++
	struct output_iterator_tag {};	// 只写迭代器, 支持++
	struct forward_iterator_tag : public input_iterator_tag {}; // 允许读写，支持++
	struct bidirectional_iterator_tag : public forward_iterator_tag {}; // 可双向移动，支持++，--
	struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // 可随机访问

	template <class iterator>
	typename iterator::iterator_type  // 获取迭代器类型
	getIteratorType(iterator) {
		return iterator::iterator_type();
	}

	template <class iterator>
	random_access_iterator_tag		// 指针型迭代器
	getIteratorType(iterator*) {
		return random_access_iterator_tag(); 
	}
}

#endif
