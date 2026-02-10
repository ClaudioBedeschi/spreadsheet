#include "FunctionFactory.h"

#include "Max.h"
#include "Mean.h"
#include "Min.h"
#include "Sum.h"

std::shared_ptr<Function> FunctionFactory::assignFunction(const std::string& functionType) {
	if (functionType == "Sum")  return sumFunction;
	if (functionType == "Min")  return minFunction;
	if (functionType == "Max")  return maxFunction;
	if (functionType == "Mean") return meanFunction;
	return nullptr;
}

std::shared_ptr<Function> FunctionFactory::sumFunction = std::make_shared<Sum>();
std::shared_ptr<Function> FunctionFactory::minFunction = std::make_shared<Min>();
std::shared_ptr<Function> FunctionFactory::maxFunction = std::make_shared<Max>();
std::shared_ptr<Function> FunctionFactory::meanFunction = std::make_shared<Mean>();
