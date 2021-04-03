//===================================================================
// Course: COMP 345
// Professor: Nora Houari
// Team: 14
// Students:
//      Adam Yafout - 40040306
//      Bryan Lee - 40079332
//      Carl Randyl Tuquero - 40067781
//      Sobhan Mehrpour - 40122438
//      Vithura Muthiah - 40062305
//===================================================================

#include "GameObservers.h"
using namespace std;

// ============================================
// GameObservers Implementation
// ============================================

Observer::~Observer()
{
}

Observer::Observer()
{
}

// ============================================
// Subject Implementation
// ============================================

Subject::Subject()
{
	_observers = new list<Observer*>;
}

Subject::~Subject()
{
	delete _observers;
}

void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
}

void Subject::Detach(Observer* o) 
{
	_observers->remove(o);
}

void Subject::Notify() 
{
	list<Observer*>::iterator i;
	for (i = _observers->begin(); i != _observers->end(); ++i) 
	{
		(*i)->Update();
	}
}