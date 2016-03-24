#ifndef __STACK_
#define __STACK_

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
class stack
{
	friend bool operator==<> (const stack& a, const stack& b);
	friend bool operator!=<> (const stack& a, const stack& b);
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef typename Sequence::iterator iterator;
	
	stack() : seq(new Sequence) {}
	~stack() { seq->Sequence();}

	T& back() {
		return (*seq)[seq->size() - 1];
	}
	
	int size() {
		return seq->size();
	}

	void pop() {
		seq->pop_back();
	}

	void push(const T& val) {
		seq->push_back(val);
	}
	
	bool empty() {
		return size() == 0;
	}

	void clear() {
		seq->clear();
	}
private:
	Sequence* seq; 
};

#endif
