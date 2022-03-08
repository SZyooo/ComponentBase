#pragma once
#include "Component.h"
#include "Invoker.h"
namespace component {
	template<typename... interfaces_types>
	class AtomicComponent : public component::IComponent
	{
	public:
		AtomicComponent(component::Invoker<interfaces_types...> invoker)
			:_invoker(invoker){}
		virtual void check(bool* ret, ...) = 0;
		virtual void* call(size_t idx, ...) = 0;
	protected:
		component::Invoker<interfaces_types...>& getInvoker()
		{
			return _invoker;
		}
	private:
		component::Invoker<interfaces_types...> _invoker;
	};
};