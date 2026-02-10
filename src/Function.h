#ifndef FUNCTION_H
#define FUNCTION_H
class Cell;

class Function {
public:
	virtual void calculate(Cell& cell)=0;

	virtual ~Function() = default;
};
#endif // FUNCTION_H
