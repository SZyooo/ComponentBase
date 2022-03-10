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
			component::Selector* selector,
			component::Loop* loop,
			component::Sequencer* sequencer,
			std::vector<size_t> call_indices) {
			loop->assignComponent(selector);
			sequencer->assignComponents({input,loop,output});
			sequencer->assignIndices(call_indices);
			this->_sequencer = sequencer;
		}

		virtual void check(bool* ret, ...) = 0;
		virtual void* call(size_t idx, ...) = 0;
		virtual ~SampleModel()
		{
			delete _sequencer;
			_sequencer = nullptr;
		}
	protected:
		IComponent* getSequencer() const { return _sequencer; }
	private:
		component::IComponent* _sequencer;
	};
};
