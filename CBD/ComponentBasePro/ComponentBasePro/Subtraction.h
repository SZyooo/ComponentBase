#pragma once
#include "AtomicComponent.h"
#include <tuple>

namespace calculator {
	double sub(std::tuple<double, double> args)
	{
		double left = std::get<0>(args);
		double right = std::get<1>(args);
		return left - right;
	}
	typedef component::Interface<double, double, double> duo_op_interface;
	class SubtractionComponent
		:public component::AtomicComponent<duo_op_interface>
	{
	public:
		SubtractionComponent()
			:AtomicComponent(component::Invoker<duo_op_interface>(component::Interface<double, double, double>(std::string("subtraction"), sub, 0., 0.)))
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
			void* ans;
			va_list args;
			va_start(args, idx);
			double left = va_arg(args, double);
			double right = va_arg(args, double);
			va_end(args);
			getInvoker().resetParameters<0, double, double>(left, right);
			ans = new double(getInvoker().invoke<0, double>());
			return ans;
		}
		static const std::string getCallOrder() { return order; }
	private:
		static std::string order;
	};
	std::string calculator::SubtractionComponent::order = "call_sub";
};