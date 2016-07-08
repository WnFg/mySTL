#include <iostream>
#include <functional>
using namespace std;

template <int N>
struct pt
{};

template <typename T1, typename tupleType>
T1 replacePg(T1 a, tupleType tp) 
{
	return a;
}

template <int N, typename tupleType>
auto replacePg(pt<N> a, tupleType tp) -> decltype(get<N>(tp)) 
{
	return get<N>(tp);
}

template <int N, typename returnType, typename callable, typename... types>
struct functor
{
private:
	callable f;
	tuple<types...> tp;
public:
	functor(tuple<types...> tp, callable f) : tp(tp), f(f) {}
	template <typename tuple_type2, typename tuple_type1, typename... pgTypes>
	static returnType invok(callable f, tuple_type2 tp2, tuple_type1 tp1, pgTypes... args)
	{
		return functor<N - 1, returnType, callable, types...>::
				invok(f, tp2, tp1, replacePg(get<N - 1>(tp1), tp2), args...);
	}
		
	template <typename... pgTypes>
	returnType operator()(pgTypes... args)
	{
		return functor<N, returnType, callable, types...>::invok(f, make_tuple(args...), tp);
	}
};

template <typename returnType, typename callable, typename... types>
struct functor<0, returnType, callable, types...>
{
private:
	callable f;
public:
	template <typename tuple_type2, typename tuple_type1, typename... pgTypes>
	static returnType invok(callable f, tuple_type2 tp2, tuple_type1 tp1, pgTypes... args)
	{
		return f(args...);
	}
};

template <typename returnType, typename T, typename... types>
functor<sizeof...(types), returnType, T, types...> myBind(T f, types... args)
{
	auto tp = make_tuple(args...);
	return functor<sizeof...(args), returnType, T, types...>(tp, f);
}

int add(int x, int y, int z) {
	return x + y + z;
}

int main()
{
	auto ff = myBind<function<decltype(add)>::result_type>(add, 1, pt<0>(), pt<1>());
	cout << ff(5, 3) << endl;
	return 0;
}
