#pragma once
#include "Loop.h"
#include <iostream>
#include "CalculatorTools.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Subtraction.h"
#include "division.h"


namespace calculator {
	class MainLoop :public component::Loop {
	public:
		MainLoop(component::IComponent* l):component::Loop(l),result(0) {}
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
			return new std::string(std::to_string(result));
		}
		static const std::string getCallOrder() { return order; }
	private:
		void processStack(std::stack<double>& number_stack, std::stack<char>& sign_stack)
		{
			const std::string error = "ERROR EXPRESSION";
			bool match = false;
			while (sign_stack.empty() == false)
			{
				char sign = sign_stack.top();
				sign_stack.pop();
				if (sign == '(')
				{
					match = true;
					break;
				}
				if (number_stack.size() < 2)
				{
					throw error;
				}
				double right = number_stack.top();
				number_stack.pop();
				double left = number_stack.top();
				number_stack.pop();
				void* tmp_res = nullptr;
				switch (sign)
				{
				case '+':
					tmp_res = getLoopComponent()->call(0, calculator::AdditionComponent::getCallOrder(), left, right);
					number_stack.push(*((double*)tmp_res));
					delete (double*)tmp_res;
					tmp_res = nullptr;
					break;
				case '-':
					tmp_res = getLoopComponent()->call(0, calculator::SubtractionComponent::getCallOrder(), left, right);
					number_stack.push(*((double*)tmp_res));
					delete (double*)tmp_res;
					tmp_res = nullptr;
					break;
				case '*':
					tmp_res = getLoopComponent()->call(0, calculator::MultiplicationComponent::getCallOrder(), left, right);
					number_stack.push(*((double*)tmp_res));
					delete (double*)tmp_res;
					tmp_res = nullptr;
					break;
				default:
					if (right == 0)
					{
						throw "ZERO DENOMINATOR ERROR";
					}
					else {
						tmp_res = getLoopComponent()->call(0, calculator::DivisionComponent::getCallOrder(), left, right);
						number_stack.push(*((double*)tmp_res));
						delete (double*)tmp_res;
						tmp_res = nullptr;
					}
					break;
				}
			}
			if (match == false)
				throw error;
		}
		std::string _expression;
		virtual void doLoop(bool loopFlag)
		{
			const std::string error = "ERROR EXPRESSION";
			std::string expression = _expression;
			expression = "(" + expression + ")";
			std::stack<char> signs;
			signs.push('(');
			std::stack<double> values;
			int cur_sign = 1;
			int cur_sign_num = 0;
			int hasDot = 1;
			double cur_number = 0;
			for (int i = 1; i < expression.length(); i++)
			{
				char c = expression[i];
				if (c == '+' || c == '-')
				{
					//operator
					if (expression[i - 1] <= '9' && expression[i - 1] >= '0' || expression[i - 1] == ')')
					{
						if (expression[i - 1] != ')')
						{
							values.push(cur_number * cur_sign);
							cur_number = 0;
							cur_sign = 1;
							hasDot = 1;
						}
						while (signs.empty() == false)
						{
							char c = signs.top();
							if (c == '(')
								break;
							signs.pop();
							if (values.size() < 2)
							{
								throw error;
							}
							double right = values.top();
							values.pop();
							double left = values.top();
							values.pop();
							if (c == '*')
							{
								void* m_res = getLoopComponent()->call(0, calculator::MultiplicationComponent::getCallOrder(), left, right);
								values.push(*((double*)m_res));
								delete (double*)m_res;
								m_res = nullptr;
							}
							else if (c == '/')
							{
								if (right == 0)
								{
									throw "ERROR:ZERO DENOMINATOR";
								}
								void* d_res = getLoopComponent()->call(0, calculator::DivisionComponent::getCallOrder(), left, right);
								values.push(*((double*)d_res));
								delete (double*)d_res;
								d_res = nullptr;
							}
							else if (c == '+')
							{
								void* a_res = getLoopComponent()->call(0, calculator::AdditionComponent::getCallOrder(), left, right);
								values.push(*((double*)a_res));
								delete (double*)a_res;
								a_res = nullptr;
							}
							else if (c == '-')
							{
								void* s_res = getLoopComponent()->call(0, calculator::SubtractionComponent::getCallOrder(), left, right);
								values.push(*((double*)s_res));
								delete (double*)s_res;
								s_res = nullptr;
							}
						}

						signs.push(c);
					}
					//sign
					else
					{
						//sign's num over flow
						if (cur_sign_num == 2)
						{
							throw error;
						}
						//+2 -1
						else
						{
							cur_sign = (c == '-') ? -1 : 1;
						}
					}
					++cur_sign_num;
				}
				else if (c == '*' || c == '/')
				{
					if ((expression[i - 1] > '9' || expression[i - 1] < '0') && expression[i - 1] != ')')
					{
						throw error;
					}
					else
					{
						if (cur_sign_num == 2)
						{
							throw error;
						}
						else {
							if (expression[i - 1] != ')')
							{
								values.push(cur_number * cur_sign);
								cur_number = 0;
								cur_sign = 1;
								hasDot = 1;
							}
							signs.push(c);
						}
					}
					++cur_sign_num;
				}
				else if (c == '.')
				{
					if (hasDot > 1)
					{
						throw error;
					}
					else
					{
						hasDot = 10;
					}
				}
				else if (c == '(')
				{
					char pre = expression[i - 1];
					if (pre == ')' || hasDot > 1 || (pre <= '9' && pre >= '0'))
					{
						throw error;
					}
					else
					{
						signs.push(c);
					}
				}
				else if (c == ')')
				{
					if (expression[i - 1] > '9' || expression[i - 1] < '0' && expression[i - 1] != ')')
					{
						throw error;
					}
					if (expression[i - 1] != ')')
					{
						values.push(cur_number * cur_sign);
						cur_number = 0;
						cur_sign = 1;
						hasDot = 1;
					}
					processStack(values, signs);
				}
				else if (c <= '9' && c >= '0')
				{
					cur_sign_num = 0;
					int val = c - '0';
					if (hasDot > 1)
					{
						cur_number += (1.0 * val / hasDot);
						hasDot *= 10;
					}
					else {
						cur_number *= 10;
						cur_number += val;
					}
				}
				else
				{
					throw error;
				}
			}
			result = values.top();
			values.pop();
		}
		static std::string order;
		double result;
	};
	std::string calculator::MainLoop::order = "call_loop";
};