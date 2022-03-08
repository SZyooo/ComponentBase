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
			:_name(name),_params(args...),_function(fun) {}
		returnType run() {
			return _function(_params);
		}
		void resetParameters(std::tuple<params...> args) const {
			_params = args;
		}
	private:
		std::string _name;
		mutable std::tuple<params...> _params;
		func _function;
	};
};