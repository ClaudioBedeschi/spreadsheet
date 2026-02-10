#ifndef SUM_H
#define SUM_H

#include "Function.h"

class Cell;

class Sum : public Function {
public:
	void calculate(Cell& cell) override;

	~Sum() override = default;
};
#endif // SUM_H
