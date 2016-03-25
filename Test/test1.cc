#include <iostream>
#include "../vector.h"
#include "../heap.h"

vector<int> v;
int main()
{
	/*v.push_back(10);
	for(int i = 0; i < 4; i++) {
		v.push_back(i);
	}
	*/
	for(int i = 10; i > 0; --i) {
		v.push_back(i);
	}
	/*for(int i = 0; i < 10; i++) {
		std::cout << v[i] << std::endl;
	}*/
	build(v.begin(), v.end());
	for(int i = 0; i < 10; i++) {
		std::cout << v[i] << std::endl;
	}
	std::cout << top(v.begin(), v[0]) << std::endl;
	return 0;
}
