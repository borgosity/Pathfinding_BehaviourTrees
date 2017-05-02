#pragma once
#include "BhtLeaf.h"
#include <memory>

class IBehaviour;

class Action :
	public BhtLeaf
{
public:
	typedef std::shared_ptr<IBehaviour> spBehaviour;
	Action();
	Action(spBehaviour behaviour);
	virtual ~Action();

	virtual Status execute(Agent * agent);

private:
	spBehaviour	m_behaviour;
};

