#pragma once
#include "Action.h"


class IBehaviour;

class ActionEvade :
	public Action
{
public:
	typedef std::shared_ptr<IBehaviour> spBehaviour;
	ActionEvade();
	ActionEvade(spBehaviour behaviour);
	virtual ~ActionEvade();

	virtual Status execute(Agent * agent);

private:
	spBehaviour	m_behaviour;
};

