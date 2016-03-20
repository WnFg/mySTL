#include <iostream>
#include "vector1.h"

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

class INT
{
public:
	typedef int* pointer;
};

int swf(int a) {
	return a;
}

struct GG
{
	int a, b;
	~GG() {
		cout << "I am die" << endl;
	}
};

GG* ans1;
GG swf(GG a) {
	cout << " asded" << endl;
	ans1 = &a;
	return a;
}
int main()
{
	vector<int> vec;
	vec.resize(5, 1);
	for(int i = 0; i < vec.size(); i++) {
		cout << vec[i] << endl;
	}
	return 0;
}
