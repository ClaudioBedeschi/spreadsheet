#ifndef CELL_H
#define CELL_H
#include <list>
#include <string>
#include <memory>

#include "Observer.h"
#include "Subject.h"
#include "Function.h"

class Cell : public Observer, public Subject {
public:
	explicit Cell(const double v=0) : value {v} {};

	void computeAndNotify();

	void update(Subject* cyclePtr) override;

	void attach() override {
		for(const auto subject : subjects)
			subject->subscribe(this);
	}
	void detach() override {
		for(const auto subject : subjects)
			subject->unsubscribe(this);
	}

	void subscribe(Observer* observer) override {
		observers.push_back(observer);
	}
	void unsubscribe(Observer* observer) override {
		observers.remove(observer);
	}

	void notify(Subject* cyclePtr) const override {
		for(const auto observer : observers)
			observer->update(cyclePtr);
	}

	void setFunction(const std::string& mathFunction);

	std::list<Cell*> getDependencies() const {
		return subjects;
	}

	void setDependencies(const std::list<Cell*>& newSubjects);

	double getValue() const {
		return value;
	}

	void setRawValueFromUser(double newValue);

	void setMathComputedValue(double updatedValue);

	~Cell() override = default;
private:
	double value {0};
	std::list<Observer*> observers;
	std::list<Cell*> subjects;
	std::shared_ptr<Function> function {nullptr};
};
#endif // CELL_H
