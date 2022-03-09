#pragma once
#include "Component.h"
#include <vector>
namespace component {

	class Selector:public component::IComponent {
	public:
		Selector(std::vector<IComponent*> components)
			:_components(components)
		{}
		virtual void check(bool* ret, ...) {}
		virtual void* call(size_t idx, ...) { return nullptr; }
		void assignComponents(const std::vector<IComponent*>& components)
		{
			for (int i = 0; i < _components.size(); i++)
			{
				delete _components[i];
				_components[i] = nullptr;
			}
			_components = components;
		}
		~Selector()
		{
			for (int i = 0; i < _components.size(); i++)
			{
				delete _components[i];
				_components[i] = nullptr;
			}
		}
	protected:
		std::vector<IComponent*> getComponents() { return _components; }
	private:
		virtual IComponent* doSelect() = 0;
		std::vector<IComponent*> _components;
	};
};