#pragma once
#include "Component.h"

namespace component {
	class Loop :public component::IComponent
	{
	public:
		Loop(IComponent* looper)
			:_loop_component(looper){}
		virtual void check(bool* ret, ...) {}
		virtual void* call(size_t idx, ...) { 
			if (_loop_component == nullptr)
				throw "NULL LOOPER::loop cannot runs without an available component!";
			return nullptr; 
		}
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
	protected:
		IComponent* getLoopComponent() const { return _loop_component; }
	private:
		IComponent* _loop_component;
		virtual void doLoop(bool loopFlag) = 0;
	};

};