#pragma once
#include "Sequencer.h"
#include "Loop.h"
#include "Selector.h"
namespace model{
	class SampleModel:public component::IComponent {
	public:
		SampleModel(
			component::IComponent* input,
			component::IComponent* output,
			component::Sequencer* sequencer,
			component::Selector* selector,
			component::Loop* loop,
			std::vector<component::IComponent*> select_froms) {
			selector->assignComponents(select_froms);
			loop->assignComponent(selector);
			sequencer->assignComponents({input,loop,output});
		}

		virtual void check(bool* ret, ...)
		{
			va_list args;
			va_start(args, ret);
			std::string order = va_arg(args, std::string);
			va_end(args, ret);
			if (order == "SampleModel")
				*ret = true;
			else
				*ret = false;
		}
		virtual void* call(size_t idx, ...) = 0;
		virtual ~SampleModel()
		{
			delete _sequencer;
		}
	private:
		component::IComponent* _sequencer;
		component::IComponent* input;
		component::IComponent* output;
		component::IComponent* selector;
		component::IComponent* loop;
	};
};
