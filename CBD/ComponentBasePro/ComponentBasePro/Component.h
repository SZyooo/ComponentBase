#pragma once
#include "Invoker.h"
namespace component {
	template<typename... Invoker_Type>
	class Component {
	public:
		virtual call(size_t idx) = 0;
	private:
		Invoker<Invoker_Type...> invoker;
	};
};