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
	typedef value_type* iterator;
	typedef value_type* pointer;
	
	vector() : start(0), finish(0), end_of_storage(0) {}

	vector(const iterator& a, const iterator& b) : start(0), finish(0), end_of_storage(0) {
		insert(start, a, b);
	}	

	vector(vector<T>& v) : start(0), finish(0), end_of_storage(0) {
		insert(start, v.begin(), v.end());	
	}
	
	~vector() { 
		tinyMemo::destroy(start, finish);
		alloc.deallocate(start, capacity_size()); 
	}

	iterator begin() { return start; }
	iterator end() { return finish; }
	T& operator[](int n) { return *(start + n); }
	int size() { return finish - start; }
	
	void push_back(const T& val) {
		if(hasSpace()) {
			*finish = val;
			++finish;
		}else {
			insert(finish, val);
		}
	}
	
	T pop_back() {
		T ret = *(finish - 1);
		tinyMemo::destroy(finish--);
		return ret;
	}
	
	// 清除[l,r)间的元素
	iterator erase(iterator l, iterator r) {
		std::uninitialized_copy(r, finish, l);
		tinyMemo::destroy(l + (finish - r), finish);
		finish -= r - l;
		return finish;
	}
	
	// 清除pos指向的元素
	iterator erase(iterator pos) {
		return erase(pos, pos + 1);
	}
	
	// 清除所有元素
	void clear() {
		erase(start, finish);
	}
	
	// 重置vector，新的大小为newSize
	iterator resize(int newSize, const T& val) {
		if(newSize <= size()) {
			erase(start + newSize, finish);	
		}else {
			int oldSize = capacity_size();
			T* newStart = allocate_and_getNewPos(newSize, oldSize);
			if(newStart != NULL) {
				std::uninitialized_copy(start, finish, newStart);
				tinyMemo::destroy(start, finish);
				alloc.deallocate(start, capacity_size());
				// 更新迭代器
				finish = newStart + size();
				start = newStart;
				end_of_storage = start + oldSize;
			}
			std::uninitialized_fill_n(finish, newSize - size(), val);
			finish = start + newSize;
		}
		return finish;
	}
	
	iterator resize(int newSize) {
		return resize(newSize, T());
	}

	// 向pos前插入元素
	void insert(iterator pos, const T& val) {
		//const iterator it = (&val) + 1;
		insert(pos, (iterator)&val, (iterator)(&val + 1));
	}
	
	T* allocate_and_getNewPos(const int& newSize, int& oldSize) {
		if(oldSize == 0){
			oldSize = newSize;
			return (T*)alloc.allocate(newSize);
		} else if(oldSize >= newSize) 
			return NULL;
		else {
			while(newSize > oldSize)
				oldSize <<= 1;
			return (T*)alloc.allocate(oldSize);
		}
	}

	void insert(iterator pos, const iterator& l, const iterator& r) {
		int now_size = r - l + size(), max_size = capacity_size();
		T *new_start, *ret;
		int newElmentSize = r - l;
		if(max_size == 0) {
	//		start = (T*)::operator new(sizeof(T)*(r - l));
			start = allocate_and_getNewPos(now_size, max_size);
			finish = start + (r - l);
			end_of_storage = finish;
			std::uninitialized_copy(l, r, start);
			return ;
		}

		if(now_size > max_size) {
			new_start = (T*) allocate_and_getNewPos(now_size, max_size);
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
