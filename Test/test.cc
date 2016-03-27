#include "map.h"

map<int, int> mp;
int main()
{
	mp.insert(1, 2);
	std::cout << (*(mp.find(1)->key.second)) << std::endl;
	return 0;
}
