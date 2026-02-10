#include <numeric>

#include "Mean.h"

#include "Cell.h"

void Mean::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty())
		cell.setValue((std::accumulate(dependencies.begin(), dependencies.end(), 0.0, [](const double sum, const Cell* c) {
			return sum + c->getValue();
		})) / static_cast<double>(dependencies.size()));
}
