#ifndef MIN_H
#define MIN_H

#include "Function.h"

class Cell;

class Min : public Function {
public:
	void calculate(Cell& cell) override;
	~Min() override = default;
};
#endif // MIN_H
