#ifndef __QUEUE_
#define __QUEUE_

#include "deque.h"

template <class T, class Sequence = deque<T> >
class queue
{
public:
	typedef T value_typle;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;

	queue() : seq(new Sequence) {}
	~queue() { seq->~Sequence();}
	void push(const T& val) {
		seq->push_back(val);
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

#endif
