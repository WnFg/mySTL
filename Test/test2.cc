#include <iostream>
#include <set>

typedef std::multiset<int>::iterator It;  // aliasing the iterator type used

int main ()
{
  int myints[]= {77,30,16,2,30,30};
  std::multiset<int> mymultiset (myints, myints+6);  // 2 16 30 30 30 77

  std::pair<It,It> ret = mymultiset.equal_range(30); //      ^        ^

 // mymultiset.erase(ret.first,ret.second);

  std::cout << "mymultiset contains:";
  for (It it=ret.first; it!=ret.second; ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
