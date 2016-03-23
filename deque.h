#ifndef __DEQUE_
#define __DEQUE_

#include "memory.h"
#include "algorithm.h"
#include "iterator_template.h"

template <class T>
struct deque_iterator : public iterator_template<tinyAr::random_access_iterator_tag, T> 
{
	typedef iterator_template<tinyAr::random_access_iterator_tag, T> base;
	using typename base::value_type;
	using typename base::pointer;
	using typename base::reference;
	using typename base::iterator_category;
	using typename base::difference_type;

	typedef deque_iterator<T> self;

	using base::node;
	pointer head;
	int mod;
	
	deque_iterator() : head(NULL) {}
	deque_iterator(pointer p1, pointer p2, int m) : base(p1), head(p2), mod(m) {}

	self& operator++() {
		//node = head + (node - head + 1)%mod;
		return shift(1);
	}

	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--() {
		//node = head + (node - head - 1 + mod)%mod;
		return shift(-1);
	}

	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}

	inline self& shift(int x) {
		node = head + (node - head + x + mod) % mod;
		return *this;
	}

	int operator- (const self& it) {
		return (node - it.node + mod) % mod;
	}

	bool operator== (const self& it) const {
		return node == it.node;
	}

	bool operator!= (const self& it) const {
		return node != it.node;
	}
};

template <class T>
class deque
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef deque_iterator<T> iterator;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;

	deque() : capacity(1) {
		head = alloc.allocate(1);
		set_iterator(start, head);
		finish = start;
	}
	
	iterator begin() { return start; }
	iterator end() { return finish; }
	
	inline void set_iterator(iterator& it, pointer node) {
		it.node = node, it.head = head, it.mod = capacity;
	}

	T& operator[] (int x) {
		iterator it = start;
		it.shift(x);
		return *it;
	}

	inline bool isFull() {
		return finish - start == capacity - 1;
	}

	int size() { return finish - start; }
	
	pointer allocate_and_copy(int n, iterator l, iterator r) {
		pointer address = (pointer)alloc.allocate(n);
		std::uninitialized_copy(l, r, address);
		return address;
	}
	
	void copy_and_update() {
		capacity <<= 1;
		int oldSize = size();
		pointer new_head = allocate_and_copy(capacity, start, finish);
		tinyMemo::destroy(start, finish);
		alloc.deallocate(head, capacity / 2);
		// 更新
		head = new_head;
		set_iterator(start, head);
		set_iterator(finish, head + oldSize);
	}
	
	void push_back(const_reference val) {
		if(isFull()) 
			copy_and_update();	
		*finish++ = val;
	}

	void push_front(const_reference val) {
		if(isFull())
			copy_and_update();
		*--start = val;
	}

	void pop_back() {
		tinyMemo::destroy(--finish);
	}
	
	void pop_front() {
		tinyMemo::destroy(start++);
	}
	
private:
	iterator start;
	iterator finish;
	pointer head;
	std::allocator<T> alloc;
	int capacity;
};


#endif
