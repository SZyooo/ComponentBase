#pragma once
namespace component {
	class ICheckable {
		virtual void check(bool* ret,...) = 0;
	};
};