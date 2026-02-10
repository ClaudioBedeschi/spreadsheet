#include <algorithm>

#include "Min.h"

#include "Cell.h"

void Min::calculate(Cell& cell) {
	auto dependencies = cell.getDependencies();
	if(!dependencies.empty())
		cell.setValue((*(std::min_element(dependencies.begin(),dependencies.end(),[](const Cell* a, const Cell* b) {
			return a->getValue() < b->getValue();
		})))->getValue());
}
