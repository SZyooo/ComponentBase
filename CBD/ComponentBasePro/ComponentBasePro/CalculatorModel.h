#pragma once
#include "Model.h"
#include "Input.h"
#include "Output.h"
#include "Calculator.h"

namespace calculator {
	class CalculatorModel:public model::SampleModel {
	public:
		CalculatorModel()
			:model::SampleModel(
				new calculator::InputComponent,
				new calculator::OutputComponent,
				new calculator::OperationSelect({
					new calculator::AdditionComponent(),
					new calculator::SubtractionComponent(),
					new calculator::MultiplicationComponent(),
					new calculator::DivisionComponent()
					}),
				new calculator::MainLoop(nullptr),
				new calculator::Controller({}, {}),
				{0,0,0}
			)
		{}
		virtual void check(bool* ret, ...) {
			va_list args;
			va_start(args, ret);
			*ret = calculator::checkOrder(order, args);
			va_end(args);
		}
		virtual void* call(size_t idx, ...) {
			return getSequencer()->call(0);
		}
		~CalculatorModel()
		{
			model::SampleModel::~SampleModel();
		}
	private:
		static std::string order;
	};
	std::string calculator::CalculatorModel::order = "run_calc";
}