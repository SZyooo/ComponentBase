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
		static const std::string getCallOrder() { return order; }
	private:
		static std::string order;
		virtual void doSequence()
		{
			void* exp = getComponents()[0]->call(getIndices()[0]);
			void* res = nullptr;
			try {
				res = getComponents()[1]->call(getIndices()[1], true, *((std::string*)exp));
			}
			catch (const char* calc_error)
			{
				res = new std::string(calc_error);
			}
			catch (std::string calc_error)
			{
				res = new std::string(calc_error);
			}
			getComponents()[2]->call(getIndices()[2], *((std::string*)res));
			delete exp;
			exp = nullptr;
			delete res;
			res = nullptr;
		}
	};
	std::string calculator::Controller::order = "call_mul";
};