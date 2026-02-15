#include <list>
#include <stdexcept>
#include <string>

#include "Cell.h"

#include "FunctionFactory.h"

void Cell::computeAndNotify() {
	if(function) {
		function->calculate(*this);
		notify(this);
	}
	else
		throw std::logic_error("No function assigned");
}

void Cell::update(Subject* cyclePtr)
{
	if(cyclePtr != this) {
		if(!cyclePtr)
			cyclePtr = this;

		function->calculate(*this);
		notify(cyclePtr);
	}
	else
		throw std::runtime_error("Err: Cycle detected");
}
void Cell::setFunction(const std::string& mathFunction) {
	function = FunctionFactory::assignFunction(mathFunction);
}

void Cell::setDependencies(const std::list<Cell*>& newSubjects)
{
	// avoids recursion by preventing being a subject of itself
	bool notThis = true;
	for(const auto subject : newSubjects) {
		if(subject == this) {
			notThis = false;
			break;
		}
	}

	if(notThis) {
		detach();
		subjects = newSubjects;
		attach();
	} else
		throw std::runtime_error("Err: Cycle detected");
}

// WARNING: this setter removes cell's dependencies and function, use only for setting pure values
void Cell::setRawValueFromUser(const double newValue) {
	value = newValue;

	detach();
	subjects.clear();
	function.reset();

	notify(nullptr);
}

// Use this setter when storing computation results
void Cell::setMathComputedValue(const double updatedValue) {
	value = updatedValue;
}
