#include <iostream>
#include "algorithm.h"

template <class T>
class A{
public:
	typedef T value_type;	
};

template <class T, class T1 = A<T> >
class B{

};

int main()
{
	
	B<int> b;
	return 0;
}
