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
	
	inline self operator+ (int x) {
		pointer p = head + (node - head + x + mod) % mod;
		return deque_iterator(p, head, mod);
	}

	inline int operator- (const self& it) const {
		return (node - it.node + mod) % mod;
	}

	inline bool operator== (const self& it) const {
		return node == it.node;
	}

	inline bool operator!= (const self& it) const {
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
	
	deque(const iterator& l, const iterator& r) : capacity(0) {
		copy_and_update(r - l + 1, l, r);
	}

	~deque() { clear();}
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

	inline int size() { return finish - start; }
	
	pointer allocate_and_copy(int n, const iterator& l, const iterator& r) {
		pointer address = (pointer)alloc.allocate(n);
		std::uninitialized_copy(l, r, address);
		return address;
	}
	
	void copy_and_update(int new_capacity, const iterator& l, const iterator& r) {
		int oldSize = size();
		pointer new_head = allocate_and_copy(new_capacity, l, r);
		if(capacity > 0 && l == start) {
			tinyMemo::destroy(start, finish);
			alloc.deallocate(head, capacity);
		}
		// 更新
		capacity = new_capacity;
		head = new_head;
		set_iterator(start, head);
		set_iterator(finish, head + oldSize);
	}
	
	void push_back(const_reference val) {
		if(isFull()) 
			copy_and_update(capacity << 1, start, finish);	
		*finish++ = val;
	}

	void push_front(const_reference val) {
		if(isFull())
			copy_and_update(capacity << 1, start, finish);
		*--start = val;
	}

	void pop_back() {
		tinyMemo::destroy(--finish);
	}
	
	void pop_front() {
		tinyMemo::destroy(start++);
	}

	bool empty() {
		return size() == 0;
	}

	void clear() {
		while(!empty()) {
			pop_back();
		}
	}

private:
	iterator start;
	iterator finish;
	pointer head;
	std::allocator<T> alloc;
	int capacity;
};

#endif
