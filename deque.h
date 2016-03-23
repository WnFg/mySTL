#ifndef __DEQUE_
#define __DEQUE_

#include "memory.h"
#include "algorithm.h"
#include "iterator_template.h"

template <class T>
struct deque_iterator : public iterator_template<T> 
{
	typedef tinyAr::random_access_iterator_tag iterator_cat;
	typedef iterator_template<T> base;
	typedef deque_iterator<T> self;

	using typename base::pointer;
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

	deque() : capacity(0), size_valueType(sizeof(T)) {}
	
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
		return start == NULL || finish - start == capacity - 1;
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
		iterator new_start = allocate_and_copy(capacity, start, finish);
		tinyMemo::destroy(start, finish);
		alloc.deallocate(head, capacity / 2);
		set_iterator(start, new_start.node);
		set_iterator(finish, new_start.shift(oldSize).node);
		head = start;
	}

	void push_front();
	void pop_back();
	void pop_front();
	
private:
	iterator start;
	iterator finish;
	iterator head;
	int size_valueType;
	std::allocator<T> alloc;
	int capacity;
};


#endif
