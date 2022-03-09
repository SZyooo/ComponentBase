#pragma once

#include <string>
#include <cstdarg>

namespace calculator {
	bool checkOrder(std::string order, va_list args)
	{
		std::string order = va_arg(args, std::string);
		if (order == order)
			return true;
		else
			return false;
	}
}