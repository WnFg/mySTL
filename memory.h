#include <cstdio>
#include <new>
#include <cstdlib>

namespace tinyMemo
{
	template <class T>
	inline T* __allocate(int n, T*)
	{
		return (T*)malloc(n); 
	}
	
	template <class T>
	inline void __delete(T* p)
	{
		free(p);
	}

	template <class T>
	inline void construct(T* p, T value)
	{
		new(p) T(value);
	}

	template <class T>
	inline void __destroy(T* ptr)
	{
		ptr->~T();
	}
	
	template <class T>
	class reall
	
	template <class T>
	class allocator 
	{
		typedef T value_type;
		typedef T* pointer;
	};

	
}
