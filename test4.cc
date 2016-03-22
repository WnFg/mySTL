#include <iostream>
using namespace std;

template <class T>
class A
{
public:
	typedef int INT;	
	
	int a;
};

template <class T>
class B : public A<T>
{
public:
	using typename A<T>::INT;
	INT b;
};

int main()
{
	B<int> a;
	a.a = 1;
	a.b = 1;
	return 0;
}
