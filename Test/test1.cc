#include "set.h"

set<int> s;
int main()
{
	s.insert(1);
	s.insert(2);
	std::cout << "asdqwe" << std::endl;
	std::cout << s.count(1) << std::endl;
	std::cout << s.count(3) << std::endl;
	return 0;
}
