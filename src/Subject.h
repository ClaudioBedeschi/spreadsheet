#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"

class Subject {
public:
	virtual void subscribe(Observer* observer)=0;
	virtual void unsubscribe(Observer* observer)=0;

	virtual void notify(Subject* cyclePtr) const = 0;

	virtual ~Subject() = default;
};
#endif // SUBJECT_H
