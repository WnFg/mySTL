#include "algorithm.h"
#include <iostream>
using namespace std;

class A
{
public:
	A() { cout << "asd" << endl;}
	A(const int& b) : a(b) {}
	int a;
};

class B : public A
{
public:
	B() { cout << "bsd" << endl; }
	B(const int& b) : A(b) { cout << "bsd" << endl;}
};

int qwe[3] = {1, 2, 3};
int main()
{
	B b(1);	
	cout << b.a << endl;
	int* p = tinyAr::find(qwe, qwe + 2, 1);
	cout << *p << endl;
	char zxc = 1;
	const int& qwz = zxc;
	cout << ((int)&qwz == (int)&zxc) << endl;
	return 0;
}
