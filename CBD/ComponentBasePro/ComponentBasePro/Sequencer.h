#pragma once
#include "Component.h"
#include <vector>
namespace component {
	class Sequencer:public component::IComponent {
	public:
		virtual void check(bool& ret, ...) = 0;
		virtual void call(void* ret, size_t idx, ...) = 0;
	protected:
		virtual void preSequenceStart() = 0;
		virtual void postSequenceStart() = 0;
	private:
		std::vector<component::IComponent&> components;
	};
};