#pragma once
#include "Composite.h"

// AND node for running a list of behaviours consecutively until one fails
class Sequence : public Composite
{
public:	
	Sequence();
	virtual ~Sequence();

	virtual Status execute(Agent * agent);

protected:
	childBehaviourList::iterator m_current;
};

