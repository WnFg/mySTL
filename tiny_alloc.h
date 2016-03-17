#ifndef __TINY_ALLOC_H
#define __TINY_ALLOC_H

#include <new>
#include <cstddef>  // ptrdiff_t, size_t
#include <cstdlib>
#include <climits>	// UINT_MAX
#include <iostream>

namespace nstd
{
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*) {
		std::set_new_handler(NULL);  // 设置内存分配错误处理机制  
		T* tmp = (T*) (::operator new((size_t)(size * sizeof(T))));
		if(tmp == NULL) {
			std::cerr << "out of memory" << std::endl;
			exit(1);
		}
		return tmp;
	}
	
	template<class T>
	inline void _deallocate(T* buffer) {
		::operator delete(buffer);
	}

	template<class T1, class T2>
	inline void _construct(T1* p, const T2& value) {
		new(p) T1(value);
	}

	template<class T>
	inline void _destroy(T* ptr) {
		ptr->~T();
	}

	template<class T>
	class allocator 
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		
		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};
		
		void construct(pointer p, const T& value) {
			_construct(p, value);
		}

		pointer allocate(size_type n, const void* hint = NULL) {
			return _allocate((difference_type)n, (pointer)NULL);
		}

		void deallocate(pointer p, size_type n) {
			_deallocate(p);
		}

		void destroy(pointer p) {
			_destroy(p);
		}

		pointer address(reference x) {
			return (pointer)&x;
		}

		const_pointer const_address(const_reference x) {
			return (const_pointer)&x;
		}

		size_type max_size() const {
			return size_type(UINT_MAX/sizeof(T));
		}
	};
}

#endif
