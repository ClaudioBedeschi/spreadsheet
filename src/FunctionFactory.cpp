#include "FunctionFactory.h"

#include <stdexcept>

#include "Max.h"
#include "Mean.h"
#include "Min.h"
#include "Sum.h"

std::shared_ptr<Function> FunctionFactory::assignFunction(const std::string& type) {
	if (type == "sum")  return sumFunction;
	if (type == "min")  return minFunction;
	if (type == "max")  return maxFunction;
	if (type == "mean") return meanFunction;
	throw std::runtime_error("Err: Unknown function type");
}

std::shared_ptr<Function> FunctionFactory::sumFunction = std::make_shared<Sum>();
std::shared_ptr<Function> FunctionFactory::minFunction = std::make_shared<Min>();
std::shared_ptr<Function> FunctionFactory::maxFunction = std::make_shared<Max>();
std::shared_ptr<Function> FunctionFactory::meanFunction = std::make_shared<Mean>();
