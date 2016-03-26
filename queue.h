#ifndef __QUEUE_
#define __QUEUE_

#include "deque.h"
#include "vector.h"
#include "heap.h"

template <class T>
bool operator== (const T& a, const T& b) {
	return a.seq == b.seq;
}

template <class T>
bool operator!= (const T& a, const T& b) {
	return a.seq != b.seq;
}

template <class T, class Sequence = deque<T> >
class queue
{
	friend bool operator==<> (const queue& a, const queue& b);
	friend bool operator!=<> (const queue& a, const queue& b);
public:
	typedef T value_typle;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef typename Sequence::iterator iterator;

	queue() : seq(new Sequence) {}
	~queue() { delete seq;}
	void push(const T& val) {
		seq->push_back(val);
	}
	
	iterator begin() {
		return seq->begin();
	}
	
	iterator end() {
		return seq->end();
	}

	T& front() {
		return *(seq->begin());
	}

	void pop() {
		seq->pop_front();
	}
	
	int size() {
		return seq->size();
	}

	bool empty() {
		return size() == 0;
	}

	void clear() {
		seq->clear();
	}
protected:
	Sequence* seq;
};


template <class T, class Sequence = vector<T>, 
		  class compare = tinyAr::less<T> >
class priority_queue
{
public:
	typedef T value_typle;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef typename Sequence::iterator iterator;

	priority_queue() : seq(new Sequence), cmp(compare()) {}
	priority_queue(iterator l, iterator r) : seq(new Sequence(l, r)), cmp(compare())
	{
		build(seq->begin(), seq->end(), cmp);
	}
	
	~priority_queue() {delete seq;}

	void push(const T& val) {
		seq->push_back(val);
		adjust_back(seq->begin(), seq->size(), cmp);
	}

	const_reference top() const {
		return __top(seq->begin(), T());	
	}

	void pop() {
		pop_front(seq->begin(), seq->end(), cmp);
		seq->pop_back();
	}
	
	bool empty() {
		return seq->size() == 0;
	}
	
	int size() {
		return seq->size();
	}
protected:
	Sequence* seq;
	compare cmp;
};
#endif
