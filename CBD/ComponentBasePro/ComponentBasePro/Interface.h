#pragma once
#include <string>
namespace component {



	// the functions in a component
	template<typename returnType,typename... params>
	class Interface{
	public:
		using func = returnType(*)(std::tuple<params...>);
		std::string name() const {
			return _name;
		}
		Interface(std::string name,func fun,params... args)
			:_name(name),params(args...),function(fun) {}
		returnType run() {
			return function(params);
		}
	private:
		std::string _name;
		std::tuple<params...> params;
		func function;
	};
};