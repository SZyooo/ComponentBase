#pragma once
#include "Sequencer.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "division.h"
#include "CalculatorTools.h"
namespace calculator {
	class Controller :public component::Sequencer
	{
	public:
		Controller(std::vector<component::IComponent*> components, std::vector<size_t> indices)
			:component::Sequencer(components,indices){}
		virtual void check(bool* ret, ...)
		{
			va_list args;
			va_start(args, ret);
			*ret = calculator::checkOrder(order, args);
			va_end(args);
		}
		virtual void* call(size_t idx, ...) {
			if (idx != 0)
			{
				throw "sequencer only has one function indexed as 0!";
			}
			else {
				doSequence();
			}
			return nullptr;
		}
	private:
		static std::string order;
		virtual void doSequence()
		{
			getComponents()[0]->call(getIndices()[0]);
		}
	};
	std::string calculator::Controller::order = "call_mul";
};