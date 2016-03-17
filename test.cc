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

int main()
{
	tt a;
	int &q = a.get();
	q++;
	cout << a.get() << endl;
//	const tt b;
//	int w = b.get();
	tt b(1);
	cout << b.get() << endl;
	return 0;

}
