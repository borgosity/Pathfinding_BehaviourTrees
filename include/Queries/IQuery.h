#pragma once
#include "IBehaviourTree.h"

class Agent;

class IQuery
{
public:
	IQuery();
	virtual ~IQuery();
	virtual Status execute(Agent * agent) = 0;
};

