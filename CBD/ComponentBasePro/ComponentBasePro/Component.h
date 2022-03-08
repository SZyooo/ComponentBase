#pragma once
#include "Check.h"
#include "Invoker.h"
#include <cstdarg>
namespace component {
	//every atomic component or composited component should implement this interface
	//return type | parameters' types
	class IComponent:public component::ICheckable { 
	public:
		//this function is used to doing some vertification
		virtual void check(bool* ret, ...) = 0;
		//ret: return | ...:parameters
		virtual void* call(size_t idx,...) = 0;
		virtual ~IComponent() {};
	};
};