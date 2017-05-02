#pragma once
#include "Composite.h"

// OR node for running a list of behaviours until one succeeds
class Selector : public Composite
{
public:
	Selector();
	virtual ~Selector();

	virtual Status execute(Agent * agent);

protected:
	childBehaviourList::iterator m_current;
};

