#pragma once
#include "Selector.h"
#include "CalculatorTools.h"

namespace calculator {
	class OperationSelect :public component::Selector {
	public:
		OperationSelect(std::vector<IComponent*> components)
			:Selector(components),call_order("") {}
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
				throw "selector only has one function indexed as 0!";
			}
			else {
				va_list args;
				va_start(args, idx);
				std::string order = va_arg(args, std::string);
				double leftVal = va_arg(args, double);
				double rightVal = va_arg(args, double);
				va_end(args);
				call_order = order;
				component::IComponent* chosenComponent = doSelect();
				if (chosenComponent == nullptr)
					ans = new double(-1);
				else
					ans = chosenComponent->call(0, leftVal, rightVal);

			}
			if (ans == nullptr)
				ans = new double(-1);
			return ans;
		}
		static const std::string getCallOrder() { return order; }
	private:
		virtual IComponent* doSelect() {
			auto components = getComponents();
			for (int i = 0; i < components.size(); i++)
			{
				bool check_val = false;
				components[i]->check(&check_val, call_order);
				if (check_val)
				{
					return components[i];
				}
			}
			return nullptr;
		}
		static std::string order;
		std::string call_order;
	};
	std::string calculator::OperationSelect::order = "select_operator";
};
