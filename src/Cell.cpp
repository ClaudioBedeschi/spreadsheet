#include "Cell.h"

#include <list>
#include <string>


#include "FunctionFactory.h"

void Cell::computeAndNotify() {
	if(function) {
		function->calculate(*this);

		notify();
	}
}

void Cell::update(Subject* subject) {
	computeAndNotify();
}
void Cell::setFunction(const std::string& mathFunction) {
	function = FunctionFactory::assignFunction(mathFunction);
	computeAndNotify();
}

void Cell::setDependencies(const std::list<Cell*>& newSubjects) {
	bool notThis = true;	// avoids being a subject of itself
	for(const auto subject : newSubjects) {
		if(subject == this) {
			notThis = false;
			break;
		}
	}

	if(notThis) {
		detach();
		this->subjects = newSubjects;
		attach();

		computeAndNotify();
	}
}

void Cell::setValue(const double newValue) {
	this->value = newValue;
	notify();

	detach();
	subjects.clear();
}
