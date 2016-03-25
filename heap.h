#ifndef __HEAP_
#define __HEAP_

#include "vector.h"
#include "algorithm.h"
#include "memory.h"

typedef tinyAr::random_access_iterator_tag random_iterator; 

template <class iterator, class compare>
void adjust_front(iterator first, int order, const int& len, const compare& cmp)
{
	iterator L, R, node = first + order - 1;
	iterator* pointer_iterator;
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
				order += *pointer_iterator - node;
				node = *pointer_iterator;
			}else 
				break;
		}
}

template <class iterator, class value_type, class compare>
void __build(iterator first, iterator last, random_iterator, value_type, const compare cmp) {
	int order;
	int len = last - first;
	iterator L, R, node;
	iterator* pointer_iterator;
	for(int i = len/2 + 1; i > 0; --i) {
		node = first + i - 1;
		order = i;
		adjust_front(first, order, len, cmp);
	}
}

template <class iterator, class compare>
void adjust_back(iterator first, int order, const compare& cmp, bool mark = true) {
	iterator node = first + order - 1, father;
	while(order != 1) {
		father = first + order / 2 - 1;
		if(mark && cmp(*father, *node))
			break;
		else {
			tinyAr::swap(*father, *node);
			node = father;
			order /= 2;
		}
	}
}

template <class iterator, class compare, class value_type>
void alter(iterator first, iterator node, value_type val, const compare& cmp) {
	int order = node - first + 1;
	*node = val;
	adjust_back(first, order, cmp);
}


// last指向最后一个元素的后一位
template <class iterator, class compare>
void pop_front(iterator first, iterator last, const compare& cmp) {
	--last;
	tinyAr::swap(*first, *last);
	adjust_front(first, 1, last - first, cmp);
}

template <class iterator, class compare>
void erase(iterator first, iterator last, int order, const compare& cmp) {
	adjust_back(first, order, cmp, false);
	pop_front(first, last, cmp);
}

template <class iterator, class value_type>
value_type top(iterator first, value_type) {
	return *first;
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
