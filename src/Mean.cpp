#include <numeric>

#include "Mean.h"

#include "Cell.h"

void Mean::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty()) {
		double sum {};
		for(const auto dep : dependencies)
			sum += dep->getValue();

		cell.setMathComputedValue(sum / static_cast<double>(dependencies.size()));
	}
}