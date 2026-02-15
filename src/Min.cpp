#include <stdexcept>

#include "Min.h"

#include "Cell.h"

void Min::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty()) {
		double min = dependencies.front()->getValue();
		for(const auto dep : dependencies)
			if(min > dep->getValue())
				min = dep->getValue();

		cell.setMathComputedValue(min);
	} else
		throw std::logic_error("Trying to compute on empty set of values");
}