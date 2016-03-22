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
		node = head + (node - head + 1)%mod;
		return *this;
	}

	self operator++(int) {
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--() {
		node = head + (node - head - 1 + mod)%mod;
		return *this;
	}

	self operator--(int) {
		self tmp = *this;
		--*this;
		return tmp;
	}
};

template <class T>
class deque
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T* iterator;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;

	deque() : start(NULL), finish(NULL), 
			  capacity(0), size_valueType(sizeof(T)) {}
	
	iterator begin() { return start; }
	iterator end() { return finish; }
	
	inline iterator getIterator(int x) {
		return head + ((start - head + x) % capacity);
	}

	T& operator[] (int x) {
		return *getIterator(x);
	}

	inline int getDiff(iterator l, iterator r) {
		return (r - l + capacity)%capacity;
	}

	inline bool isFull() {
		return start == NULL || getDiff(start, finish) == capacity - 1;
	}

	int size() { return getDiff(start, finish); }
	
	pointer allocate_and_copy(int n, iterator l, iterator r) {
		pointer address = (pointer)alloc.allocate(n);
		std::uninitialized_copy(l, r, address);
		return address;
	}
	
	void copy_and_update() {
		capacity <<= 1;
		iterator new_start = allocate_and_copy(capacity, start, finish);
		tinyMemo::destroy(start, finish);
		alloc.deallocate()
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
