#include <iostream>
//#include <map>
#include "map.h"
//using namespace std;

class A
{
public:
	int f() {
		std::cout << "AAA" << std::endl;
		return 0;
	}
	~A() { std::cout << "asd" << std::endl;}
};

class B : public A
{
public:
	A a;
	int f() {
		return A::f();
	}
	B()  {}
};

map<int, int> mp;
int main()
{
	B b;
	b.f();
	mp.insert(2, 1);
	mp.insert(1, 3);
	std::cout << (mp.begin()->second) << std::endl;
	std::cout << mp[2] << std::endl;
	mp.lower_bound(2);
	std::cout << mp.size() << std::endl;
	mp[4];
	std::cout << mp.size() << std::endl;
	return 0;
}
