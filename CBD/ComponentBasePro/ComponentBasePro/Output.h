#pragma once
#include "AtomicComponent.h"
#include <iostream>
#include <tuple>
#include "CalculatorTools.h"


namespace calculator {
	void output(std::tuple<std::string> exp)
	{
		std::cout << std::get<0>(exp) << std::endl;
	}

	typedef component::Interface<void,std::string> output_res;
	class OutputComponent
		:public component::AtomicComponent<output_res>
	{
	public:
		OutputComponent()
			:AtomicComponent<output_res>(component::Invoker<output_res>(component::Interface<void,std::string>("output", output, "")))
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
			if (idx != 0)
			{
				throw "Output Component only has one functionality indexed as 0!";
			}
			va_list args;
			va_start(args, idx);
			std::string value = va_arg(args,std::string);
			va_end(args);
			std::string outPutStr = "the result = " + value;
			getInvoker().resetParameters<0, std::string>(outPutStr);
			getInvoker().invoke<0,void>();
		}
		static const std::string getCallOrder() { return order; }
	private:
		static std::string order;
	};
	std::string calculator::OutputComponent::order = "call_output";
};