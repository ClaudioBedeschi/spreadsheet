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
	}
}
