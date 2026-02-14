#ifndef OBSERVER_H
#define OBSERVER_H
class Subject;

class Observer {
public:
	virtual void update(Subject* cyclePtr)=0;

	virtual void attach()=0;
	virtual void detach()=0;

	virtual ~Observer() = default;
};
#endif // OBSERVER_H
