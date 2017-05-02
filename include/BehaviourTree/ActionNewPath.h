#pragma once
#include "Action.h"


class IBehaviour;

class ActionNewPath :
	public Action
{
public:
	typedef std::shared_ptr<IBehaviour> spBehaviour;
	ActionNewPath();
	ActionNewPath(spBehaviour behaviour);
	virtual ~ActionNewPath();

	virtual Status execute(Agent * agent);

private:
	spBehaviour	m_behaviour;
};

