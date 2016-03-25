#ifndef __QUEUE_
#define __QUEUE_

#include "deque.h"

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

	queue() : seq(new Sequence) {}
	~queue() { delete seq;}
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
