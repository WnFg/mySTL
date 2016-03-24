#ifndef __STACK_
#define __STACK_

#include "deque.h"

template <class T, class Sequence = deque<T> >
class stack
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T* const_pointer;
	typedef const T& const_reference;
	typedef typename Sequence::iterator iterator;
	
	stack() : seq(new Sequence) {}
	~stack() { clear(); delete seq;}

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

	void clear() {
		seq->clear();
	}
private:
	Sequence* seq; 
};

#endif
