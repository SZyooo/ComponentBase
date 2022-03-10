#pragma once
#include "AtomicComponent.h"
#include <tuple>
#include "CalculatorTools.h"

namespace calculator {

	std::string readExpression(std::tuple<>)
	{
		std::string exp;
		std::cout << "input your arithmetic expression:" << std::endl;
		std::cin >> exp;
		return exp;
	}
	typedef component::Interface<std::string> read_exp;
	class InputComponent :public component::AtomicComponent<read_exp> {
	public:
		InputComponent()
			:AtomicComponent<read_exp>(component::Invoker<read_exp>(component::Interface<std::string>(std::string("readInput"), readExpression)))
		{}
		virtual void check(bool* ret, ...)
		{
			va_list args;
			va_start(args, ret);
			*ret = calculator::checkOrder(order, args);
			va_end(args);
		}
		virtual void* call(size_t idx, ...)
		{
			void* ans = nullptr;
			if (idx != 0)
			{
				throw "InputComponent only has one functionality indexed as 0";
			}
			else {
				ans = new std::string(getInvoker().invoke<0, std::string>());
			}
			return ans;
		}
		static const std::string getCallOrder() { return order; }
	private:
		static std::string order;
	};
	std::string calculator::InputComponent::order = "call_input";
};