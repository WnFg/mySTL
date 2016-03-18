#ifndef __VECTOR_
#define __VECTOR_

#include <new>
#include <cstdlib>
#include <memory>
#include "memory.h"
#include <iostream>

template <class T>
class vector
{
public:
	typedef T value_type;
	typedef T* iterator;
	typedef T* pointer;
	vector() : start(0), finish(0), end_of_storage(0) {}

	vector(const iterator& a, const iterator& b) : start(0), finish(0), end_of_storage(0) {
		insert(start, a, b);
	}	

	vector(vector<T>& v) : start(0), finish(0), end_of_storage(0) {
		insert(start, v.begin(), v.end());	
	}
	
	~vector() { tinyMemo::destroy(start, finish);
		std::cout << "asdasd" << std::endl;
		alloc.deallocate(start, capacity_size()); }

	iterator begin() { return start; }
	iterator end() { return finish; }
	T& operator[](int n) { return *(start + n); }
	int size() { return finish - start; }
	
	void push_back(T val) {
		if(hasSpace()) {
			*finish = val;
			++finish;
		}else {
			insert(finish, val);
		}
	}
	
	T pop_back() {
		T ret = *finish;
		tinyMemo::destroy(finish--);
		return ret;
	}
	// 像pos前插入元素
	void insert(iterator pos, T val) {
		//const iterator it = (&val) + 1;
		insert(pos, &val, (&val) + 1);
	}
	
	void insert(iterator pos, iterator l, iterator r) {
		int now_size = r - l + size(), max_size = capacity_size();
		T *new_start, *ret;
		int newElmentSize = r - l;
		if(max_size == 0) {
			start = (T*)::operator new(sizeof(T)*(r - l));
			finish = start + (r - l);
			end_of_storage = finish;
			std::uninitialized_copy(l, r, start);
			return ;
		}

		if(now_size > max_size) {
			while(max_size < now_size) {
				max_size <<= 1;
			}
			new_start = (T*) alloc.allocate(max_size);
			std::uninitialized_copy(start, pos, new_start);
			ret = new_start + (pos - start);
			std::uninitialized_copy(l, r, ret);
			ret += r - l;
			std::uninitialized_copy(pos, finish, ret);
			
			// 销毁原始数据
			tinyMemo::destroy(start, finish);  			
			alloc.deallocate(start, size());
			// 更新迭代器
			start = new_start;
			finish = new_start + now_size;
			end_of_storage = new_start + max_size;
			}else{
				if(pos == start) {
					std::uninitialized_copy(l, r, start + (r - l));
				}else
					for(iterator i = finish - 1, j = i + newElmentSize; i != pos - 1; i--, j--)
						*j = *i;
					
				for(int i = 0; i < newElmentSize; i++)
					*(pos + i) = *(l + i);
			// 更新迭代器
				finish = start + now_size;
		}
	}
private:
	iterator start;
	iterator finish;
	iterator end_of_storage;
	std::allocator<T> alloc;
	inline bool hasSpace() { return end_of_storage > finish;}
	inline int capacity_size() { return end_of_storage - start; }
};

#endif
