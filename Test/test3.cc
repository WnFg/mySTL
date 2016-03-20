#include <iostream>
using namespace std;

struct C{
	C() {}
	C(const C& a) { cout << "asdqwe" << endl; }
};

C f() {
	C a;
	return a;
}
int main()
{
	f();
	C d;
	C w = d; 
	return 0;
}
