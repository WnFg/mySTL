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
	GG wsr = swf(GG());
	//const GG& wsr = GG();
	//int& wat = 2 + 2;
	//swf(GG());
	cout << (&wsr == ans1) << " dfg" << endl;
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
	vec.erase(vec.begin());
	cout << vec.size() << " asd" << endl;
	vec.push_back(1);
	vec.push_back(2);
	cout << vec.pop_back() << endl;
	volatile const int ap = 1;

	int* app = (int*)(&ap);
	*app = 3;
	cout << (*app) << " gfg"<< endl;
	cout << ap << " cvb" << endl;
	cout << (app == (&ap)) << " sd" << endl;
	//const vector<fff>::iterator qwex = qwez;
	
	int qwe = 1;
	const int* qe = &qwe;
	const int* qwer = qe;
	(int)qe;
	return 0;
}
