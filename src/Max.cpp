#include <algorithm>

#include "Max.h"

#include "Cell.h"

void Max::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty())
		cell.setValue((*(std::max_element(dependencies.begin(),dependencies.end(),[](const Cell* a, const Cell* b) {
			return a->getValue() < b->getValue();
		})))->getValue());
}
