#include "../vector.h"
#include "../algorithm.h"
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
vector<int> vec;
int main()
{
	for(int i = 0; i < 10000000; i++) {
		vec.push_back(i);
	}
	cout << vec[123353] << endl;
	return 0;
}
