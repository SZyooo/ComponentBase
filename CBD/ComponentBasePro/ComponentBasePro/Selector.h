#pragma once
#include "Component.h"
#include <vector>
namespace component {

	class Selector:component::IComponent {
	public:
		virtual void check(bool& ret, ...) = 0;
		virtual void call(void* ret,size_t idx, ...) = 0;
		//it's responsible for choosing a proper component to 
		virtual component::IComponent& select() = 0;
	protected:
		//it's called before the calling of call
		virtual void preCall() = 0;
		//it's called after the calling of call
		virtual void postCall() = 0;
	private:
		std::vector<IComponent&> components;
	};
};