#pragma once
#include "AtomicComponent.h"
#include <iostream>
#include <tuple>
#include "CalculatorTools.h"


namespace calculator {
	void output(std::tuple<double> exp)
	{
		std::cout << std::get<0>(exp) << std::endl;
	}

	typedef component::Interface<void,double> output_res;
	class OutputComponent
		:public component::AtomicComponent<output_res>
	{
	public:
		OutputComponent()
			:AtomicComponent<output_res>(component::Invoker<output_res>(component::Interface<void,double>("output", output, 0.)))
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
			double value = va_arg(args,double);
			va_end(args);
			getInvoker().resetParameters<0, double>(value);
			getInvoker().invoke<0,void>();
		}
	private:
		static std::string order;
	};
	std::string calculator::OutputComponent::order = "call_output";
};