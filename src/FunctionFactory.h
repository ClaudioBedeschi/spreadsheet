#ifndef FUNCTIONFACTORY_H
#define FUNCTIONFACTORY_H
#include <memory>
#include <string>

#include "Function.h"

class Cell;

class FunctionFactory {
public:
	static std::shared_ptr<Function> assignFunction(const std::string& type);
private:
	static std::shared_ptr<Function> sumFunction;
	static std::shared_ptr<Function> minFunction;
	static std::shared_ptr<Function> maxFunction;
	static std::shared_ptr<Function> meanFunction;
};
#endif // FUNCTIONFACTORY_H
