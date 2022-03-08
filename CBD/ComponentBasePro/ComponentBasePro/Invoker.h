#pragma once
#include <string>
#include "Interface.h"
namespace component {


	//invoker of the functions in components
	//inters: such as Interface<int,int>
	template<typename... inters>
	class Invoker {
	public:
		
		//..................extract tuple from paramters...........
		template<typename first, typename... remaining>
		std::tuple<first, remaining...> extractTuple(first f, remaining... r)
		{
			std::tuple<first> tup(f);
			auto left = extractTuple(r...);
			return std::tuple_cat(tup, left);
		}
		template<typename T>
		std::tuple<T> extractTuple(T t)
		{
			std::tuple<T> tup(t);
			return tup;
		}
		//.........................................................


		Invoker(inters... itfs)
			:_function_list(extractTuple(itfs...))
		{
			_func_nums = std::tuple_size<decltype(_function_list)>::value;
		}
		//template<typename... T>
		//void addFunc(Interface<T...> interface) {
		//	std::tuple_cat(_function_list, std::tuple<Interface<T...>>(interface));
		//	++_func_nums;
		//}

		template<size_t N, typename retType>
		retType invoke()
		{
			return std::get<N>(_function_list).run();
		}
	private:
		std::tuple<inters...> _function_list;
		size_t _func_nums;
		//template<typename retType,size_t TN, size_t N = 0>
		//retType _invoke()
		//{
		//	if (N + 1 != TN)
		//	{
		//		return _invoke<retType,TN,N + 1>();
		//	}
		//	else if (N + 1 > TN)
		//		throw "The index of function is out of range!";
		//	else
		//	{
		//		auto fun = std::get<N>(_function_list);
		//		return fun.run();
		//	}
		//}
	};
};