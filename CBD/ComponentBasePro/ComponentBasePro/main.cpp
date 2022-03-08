#include <iostream>
#include <tuple>
#include "Interface.h"
#include "Invoker.h"
//template<typename T>
//std::tuple<T> extractTuple(T v)
//{
//	return std::tuple<T>(v);
//}
//
//template<typename first,typename... args>
//std::tuple<first,args...> extractTuple(first f,args... values)
//{
//	std::tuple<first> tup(f);
//	auto remaining = extractTuple(values...);
//	return std::tuple_cat(tup, remaining);
//}

void fun1(std::tuple<>)
{
	std::cout << "success" << std::endl;
}
void fun2(std::tuple<>)
{
	std::cout << "success2" << std::endl;
}
void fun3(std::tuple<>)
{
	std::cout << "success3" << std::endl;
}
int add(std::tuple<int, int> params)
{
	int left, right;
	std::tie(left, right) = params;
	return left + right;
}
int main(){
	component::Interface<void> itf1(std::string("test"), fun1);
	component::Interface<void> itf2(std::string("row"), fun2);
	component::Interface<void> itf3(std::string("column"), fun3);
	int left = 4;
	int right = 5;
	component::Interface<int, int, int> itf4(std::string("add"),add,left,right);
	component::Invoker<
		component::Interface<void>, 
		component::Interface<void>, 
		component::Interface<void>,
		component::Interface<int,int,int> >
		invoker(itf1,itf2,itf3,itf4);
	std::cout << invoker.invoke<3,int>();
}