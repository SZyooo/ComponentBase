#pragma once
#include "Component.h"
#include <vector>
namespace component {
	class Sequencer:public component::IComponent {
	public:
		Sequencer(std::vector<component::IComponent*> components,std::vector<size_t> indices)
			:_components(components),_call_indicies(indices){
			if (components.size() != indices.size())
				throw"each component needs an single index to verify the chosen function of it";
		}
		virtual void check(bool* ret, ...) {}
		virtual void* call(size_t idx, ...) { return nullptr; }
		void assignComponents(const std::vector<component::IComponent*>& components)
		{
			for (int i = 0; i < _components.size(); i++)
			{
				delete _components[i];
				_components[i] = nullptr;
			}
			_components = components;
		}
		void assignIndices(const std::vector<size_t>& indices)
		{
			_call_indicies = indices;
		}
		~Sequencer()
		{
			for (int i = 0; i < _components.size(); i++)
			{
				delete _components[i];
				_components[i] = nullptr;
			}
		}
	protected:
		virtual void doSequence() = 0;
		std::vector<component::IComponent*> getComponents() const { return _components; }
		std::vector<size_t> getIndices() const { return _call_indicies; }
	private:
		std::vector<component::IComponent*> _components;
		std::vector<size_t> _call_indicies;
	};
};