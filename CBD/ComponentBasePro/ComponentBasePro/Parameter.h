#pragma once
#include<tuple>

namespace component {
	template<typename... param_types>
	class Parameter {
	public:
		template<typename firstType,typename...left>
		std::tuple<firstType, left...> extractTuple(firstType fT,left...remaining) {
			std::tuple<firstType> _tuple_(fT);
			std::tuple<left...> otherParams = extractTuple(remaining...);
			return std::tuple_cat(_tuple_, otherParams);
		}
		Parameter(param_types... args)
			:_parameters(extractTuple(args...)){}
		template<size_t N, typename T>
		void setParameter(T val)
		{
			std::get<N>(_parameters) = val;
		}
		template<size_t N, typename T>
		T fetchParameter()
		{
			return std::get<N>(_parameters);
		}
	private:
		std::tuple<param_types...> _parameters;
	};
}