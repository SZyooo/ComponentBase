#pragma once
#include "Component.h"

namespace component {
	class Loop :public component::IComponent
	{
	public:
		Loop(IComponent* looper)
			:_loop_component(looper){
			if (looper == nullptr)
				throw "NULL LOOPER::cannot init a looper without available component!";
		}
		virtual void check(bool* ret, ...) {}
		virtual void* call(size_t idx, ...) { return nullptr; }
		void assignComponent(component::IComponent* component_)
		{
			if (_loop_component != nullptr)
				delete _loop_component;
			_loop_component = component_;
		}
		~Loop()
		{
			delete _loop_component;
			_loop_component = nullptr;
		}
	private:
		IComponent* _loop_component;
		virtual void doLoop(bool loopFlag) = 0;
	};

};