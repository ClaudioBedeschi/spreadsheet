#ifndef MEAN_H
#define MEAN_H

#include "Function.h"

class Cell;

class Mean : public Function {
public:
	void calculate(Cell& cell) override;
	~Mean() override = default;
};
#endif // MEAN_H
