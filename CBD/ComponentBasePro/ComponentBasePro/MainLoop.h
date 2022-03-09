#pragma once
#include "Loop.h"
#include <iostream>
#include "CalculatorTools.h"

namespace calculator {
	class MainLoop :component::Loop {
	public:
		MainLoop(component::IComponent* l):component::Loop(l){}
		virtual void check(bool* ret, ...) {
			va_list args;
			va_start(args, ret);
			*ret = calculator::checkOrder(order, args);
			va_end(args);
		}
		virtual void* call(size_t idx, ...) { 
			if (idx != 0)
			{
				throw "Loop component only has one function indexed as 0";
			}
			va_list args;
			va_start(args, idx);
			bool flag = va_arg(args, bool);
			std::string expression = va_arg(args, std::string);
			va_end(args);
			_expression = expression;
			doLoop(flag);
			return new double(-807.);
		}

	private:
		std::string _expression;
		virtual void doLoop(bool loopFlag)
		{
			while (loopFlag)
			{
				std::cout << "figure expression" << std::endl;
				loopFlag = false;
			}
		}
		static std::string order;
	};
	std::string calculator::MainLoop::order = "call_loop";
};