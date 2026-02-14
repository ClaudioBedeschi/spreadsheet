#include "Cell.h"

#include <list>
#include <string>


#include "FunctionFactory.h"

void Cell::computeAndNotify(Subject* cyclePtr) {
	if(function) {
		function->calculate(*this);

		notify(cyclePtr);
	}
}

void Cell::update(Subject* cyclePtr) {
	if(cyclePtr != this)
		computeAndNotify(cyclePtr);
}
void Cell::setFunction(const std::string& mathFunction) {
	function = FunctionFactory::assignFunction(mathFunction);
	computeAndNotify();
}

void Cell::setDependencies(const std::list<Cell*>& newSubjects) {
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

		// to prevent dependency cycles bigger than trivial recursion,
		// "this" is passed down the observers' path
		computeAndNotify(this);
	}
}

// WARNING: this setter removes cell's dependencies and function, use only for setting pure values
void Cell::setRawValueFromUser(const double newValue) {
	value = newValue;
	notify(nullptr);

	detach();
	subjects.clear();
	function.reset();
}

// Use this setter when storing computation results
void Cell::setMathComputedValue(const double updatedValue) {
	value = updatedValue;
}
