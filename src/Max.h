#ifndef MAX_H
#define MAX_H

#include "Function.h"

class Cell;

class Max : public Function {
public:
	void calculate(Cell& cell) override;
	~Max() override = default;
};
#endif // MAX_H
