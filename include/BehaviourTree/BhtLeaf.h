#pragma once
#include "IBehaviourTree.h"

class BhtLeaf :
	public IBehaviourTree
{
public:
	BhtLeaf();
	virtual ~BhtLeaf();

	virtual Status execute(Agent * agent) = 0;
};

