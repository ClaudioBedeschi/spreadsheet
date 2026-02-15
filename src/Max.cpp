#include <stdexcept>

#include "Max.h"

#include "Cell.h"

void Max::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty()) {
		double max = dependencies.front()->getValue();
		for(const auto dep : dependencies)
			if(max < dep->getValue())
				max = dep->getValue();

		cell.setMathComputedValue(max);
	} else
		throw std::logic_error("Trying to compute on empty set of values");
}
