#include "Sum.h"

#include "Cell.h"

void Sum::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty()) {
		double sum {};
		for(const auto dep : dependencies)
			sum += dep->getValue();

		cell.setMathComputedValue(sum);
	}
}