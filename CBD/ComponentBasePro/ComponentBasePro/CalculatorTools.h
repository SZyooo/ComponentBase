#pragma once

#include <string>
#include <cstdarg>
#include <stack>

namespace calculator {
	bool checkOrder(std::string order, va_list args)
	{
		std::string input_order = va_arg(args, std::string);
		if (input_order == order)
			return true;
		else
			return false;
	}



}