#include <iostream>
#include "list.h"
using namespace std;
int main()
{
	__list_node<int> node(5);
	__list_iterator<__list_node<int> > it(&node);
	cout << it->data << endl;
	cout << node.data << endl;
	return 0;
}
