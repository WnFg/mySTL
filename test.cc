#include <iostream>
#include "vector.h"

using namespace std;

class tt
{
public:
	tt() : a(1) {}
	tt(int) { a = 0; tt(); }
	int& get() {return a;}
	const int& get() const { return a;}
private:
	int a;
};

void f(const int*) {}

class fff
{
public:
	~fff() {cout << "123" << endl;}
};

void ffq(const int& a){ cout << a << endl;}

int main()
{
	tt a;
	int &q = a.get();
	q++;
	ffq(1);
	cout << a.get() << endl;
	tinyMemo::destroy(&a);
//	vector<fff> vec;
//	vec.push_back(fff());
	vector<int> vec;
	vec.push_back(1);
//	cout << vec[0] << endl;
	/*int aaa = 1;
	int *ppp = &aaa;
	fff* ww = new fff;
	ww->~fff();*/
/*	//	const tt b;
//	int w = b.get();
//	int(0);
	const int www = 1;
	const int* p = (&www) + 1;
//	const int*& qqq = &www;
	f(&www);
	tt b(1);
	cout << b.get() << endl;
*/
	return 0;
}
