#ifndef __HEAP_
#define __HEAP_

#include "vector.h"
#include "algorithm.h"
#include "memory.h"

typedef tinyAr::random_access_iterator_tag random_iterator; 

template <class iterator, class value_type, class compare>
void __build(iterator first, iterator last, random_iterator, value_type, compare cmp) {
	int order;
	int len = last - first;
	iterator L, R, node;
	iterator* pointer_iterator;
	for(int i = len/2 + 1; i > 0; --i) {
		node = first + i - 1;
		order = i;
		while(order*2 <= len) {
			L = first + order*2 - 1;
			if(order*2 < len) {
				R = L + 1;
				if(cmp(*L , *R)) 
					pointer_iterator = &L;
				else
					pointer_iterator = &R;
			}else {
				pointer_iterator = &L;
			}

			if(cmp(**pointer_iterator, *node)) {
				tinyAr::swap(**pointer_iterator, *node);
				node = *pointer_iterator;
				order = *pointer_iterator - first + 1;
			}else 
				break;
		}
	}
}

template <class iterator, class compare>
void build(iterator first, iterator last, compare cmp) {
	typedef typename tinyMemo::traits<iterator>::iterator_category iterator_type;
	typedef typename tinyMemo::traits<iterator>::value_type value_type;
	__build(first, last, iterator_type(), value_type(), cmp);
}

template <class iterator>
void build(iterator first, iterator last) {
	typedef typename tinyMemo::traits<iterator>::value_type value_type;
	build(first, last, tinyAr::less<value_type>());
}

#endif
