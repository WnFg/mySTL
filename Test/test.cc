#include "queue.h"
#include <iostream>
using namespace std;

template <class T>
class A{};

template <class T = int>
void f() {};

template <class T, class T1 = A<T> >
class B{};

int main()
{
	B<int> a;
	return 0;
}
