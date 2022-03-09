#pragma once
namespace component {
	class ICheckable {
	public:
		virtual void check(bool* ret,...) = 0;
		virtual ~ICheckable()=0 {}
	};
};