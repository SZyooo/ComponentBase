#pragma once
#include "AtomicComponent.h"
#include <set>
#include <tuple>
namespace component {
	static std::set<std::string> _invoke_order;
	double add(std::tuple<double, double> args) {
		double l, r;
		std::tie(l, r) = args;
		return l + r;
	}
	double minus(std::tuple<double, double> args) {
		double l, r;
		std::tie(l, r) = args;
		return l - r;
	}
	double multiply(std::tuple<double, double> args) {
		double l, r;
		std::tie(l, r) = args;
		return l * r;
	}
	double division(std::tuple<double, double> args) {
		double l, r;
		std::tie(l, r) = args;
		if (r == 0)
			throw "denominator cannot be zero!";
		else
			return l / r;
	}


	//template<typename... interfaces_types>
	typedef component::Interface<double, double, double> duo_op;
	class SimpleArithmeticAtomicComponent 
		:public AtomicComponent<duo_op, duo_op, duo_op, duo_op>
	{
	public:
		SimpleArithmeticAtomicComponent()
			:AtomicComponent<duo_op, duo_op, duo_op, duo_op>(component::Invoker<duo_op,duo_op,duo_op,duo_op>
				(
					duo_op(std::string("add"), add, 0, 0),
					duo_op(std::string("minus"), minus, 0, 0),
					duo_op(std::string("multiply"), multiply, 0, 0),
					duo_op(std::string("division"), division, 0, 0)
				)		
			) 
		
		{
			_invoke_order.insert("call:+");
			_invoke_order.insert("call:-");
			_invoke_order.insert("call:*");
			_invoke_order.insert("call:/");
		}
		virtual void check(bool* ret, ...)
		{
			va_list args;
			va_start(args, ret);
			std::string order = va_arg(args, std::string);
			va_end(args);
			if (_invoke_order.find(order) == _invoke_order.end())
			{
				*ret = false;
			}
			else *ret = true;
		}
		virtual void* call(size_t idx, ...)
		{
			void* ret = nullptr;
			if (idx > 3 || idx < 0)
				throw "call out of range";
			va_list args;
			va_start(args, idx);
			int left = va_arg(args, double);
			int right = va_arg(args, double);
			va_end(args);
			switch (idx)
			{
			case 0:
				getInvoker().resetParameters<0,double, double>(left, right);
				ret = new double(getInvoker().invoke<0, double>());
				break;
			case 1:
				getInvoker().resetParameters<1,double, double>(left, right);
				ret = new double(getInvoker().invoke<1, double>());
				break;
			case 2:
				getInvoker().resetParameters<2,double, double>(left, right);
				ret = new double(getInvoker().invoke<2, double>());
				break;
			case 3:
				getInvoker().resetParameters<3,double, double>(left, right);
				ret = new double(getInvoker().invoke<3, double>());
				break;
			default:
				ret = new double(-1);
				break;
			}
			return ret;
		}
		static std::string plus_order() { return std::string("call:+"); }
		static std::string minus_order() { return std::string("call:-"); }
		static std::string multiply_order() { return std::string("call:*"); }
		static std::string division_order() { return std::string("call:/"); }
	private:
	};
};